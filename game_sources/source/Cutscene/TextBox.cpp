#include "stdafx_game.h"

#include <sstream>

#include "Cutscene/TextBox.h"
#include "General/ResourceHandler.h"
#include <boost/smart_ptr/shared_ptr.hpp>
#include "Cutscene/Character.h"
#include "LogMessageManager.h"

extern const wchar_t * g_text;

TextBox::TextBox()
	: m_text(make_unique<sf::Text>())
{
	m_isHidden = true;
}

void TextBox::Initialize(shared_ptr<ResourceHandler> resources)
{
	Fonts::Id id = Fonts::DEFAULT;
	if (!resources->LoadFont(Fonts::DEFAULT, "Resources/16105.ttf"))
	{
		id = Fonts::TIMES_NEW_ROMAN;
		auto success = resources->LoadFont(id, "Resources/times-new-roman.ttf");
		assert(success);
	}
	
	m_background.setSize({350.0f, 150.0f});
	m_background.setFillColor(sf::Color::Black);
	m_background.setOutlineColor(sf::Color::White);
	m_background.setOutlineThickness(5.0f);

	if (auto ptr = resources->GetFont(id))
	{
		const int fontSize = 35;

		m_text->setFont(*ptr);
		m_text->setCharacterSize(fontSize);
		m_text->setFillColor(sf::Color::White);
		m_text->move(10.0f, -10.0f);

		auto && glyph = ptr->getGlyph(L'Щ', fontSize, false);
		sf::Vector2f size = {
			glyph.bounds.width,
			glyph.bounds.height
		};
		const auto lineSpacing = ptr->getLineSpacing(sf::Uint32(fontSize));

		auto && backgroundBBox = GetBBox();
		auto area = backgroundBBox.width * backgroundBBox.height;

		m_symbolWidth = size.x;
		m_maxSymbolsInPhrase = static_cast<size_t>(std::floor(area / float(size.x * (size.y + lineSpacing))));
		m_maxSymbolsInRow = static_cast<size_t>(std::floor(backgroundBBox.width / float(size.x)));
	}

	SplitOnPhrases(g_text);
}

void TextBox::Update(float dt)
{	
	if (m_onPause)
	{
		return;
	}

	if (m_delayToNextPhrase > 0.0f)
	{
		m_delayToNextPhrase -= dt;
		return;
	}

	if (m_phraseToShow == m_sourcePhrases.size())
	{
		m_isHidden = true;
		return;
	}

	size_t symbolsInPhrase = 0;
	auto && phrase = m_sourcePhrases[m_phraseToShow];
	for (auto i = 0; i < std::min(m_maxLineInPhrase, phrase.size()); ++i)
	{
		symbolsInPhrase += phrase[i].length();
	}

	m_delayToNextPhrase = symbolsInPhrase / m_symbolsPerSecond;

	m_phraseToShow = m_phraseIndex;
	++m_phraseIndex;
}

void TextBox::Call(GameEvent event, shared_ptr<Entity> sender)
{
	if (auto character = std::dynamic_pointer_cast<Character>(sender))
	{
		switch (event)
		{
		case GameEvent::CUTSCENE_CHARACTER_MOVING_COMPLETED:
			LOG_MESSAGE("Text showing started...");
			m_onPause = false;
			m_isHidden = false;
			break;
		default:
			LOG_ERROR("Character send to text box unknown event %1%!", static_cast<size_t>(event));
		}
		
	}
}

sf::FloatRect TextBox::GetBBox() const
{
	return getTransform().transformRect(m_background.getGlobalBounds());
}

void TextBox::SplitOnPhrases(const wchar_t * message)
{
	vector<std::wstring> sourceWords;
	{
		std::wstringstream splitter(message);
		std::wstring word;
		while (true)
		{
			splitter >> word;
			if (word.empty())
			{
				break;
			}

			sourceWords.emplace_back(std::move(word));
		}	
	}
	
	size_t wordIndex = 0;
	while (wordIndex != sourceWords.size())
	{
		vector<std::wstring> lines;
		size_t symbolNumberInPhrase = 0;

		while (symbolNumberInPhrase < m_maxSymbolsInPhrase && wordIndex < sourceWords.size() && lines.size() < m_maxLineInPhrase)
		{
			std::wstring line;
			size_t wordsInRow = 0;
			size_t symbolsInRow = 0;

			auto & word = sourceWords[wordIndex];
			while (symbolsInRow + word.length() + 2 < m_maxSymbolsInRow || wordsInRow == 0) // +1 is space, +1 is '\n'
			{
				symbolsInRow += word.length() + 1;
				line += word + L' ';

				++wordsInRow;
				if (wordIndex + wordsInRow >= sourceWords.size())
				{
					break;
				}

				word = sourceWords[wordIndex + wordsInRow];	
			}

			wordIndex += wordsInRow;
			symbolNumberInPhrase += line.length();
			
			lines.emplace_back(std::move(line));
		}

		m_sourcePhrases.emplace_back(std::move(lines));
	}
}

void TextBox::UpdateText() const
{
	if (m_phraseToShow == m_sourcePhrases.size())
	{
		return;
	}

	std::wstring text;
	
	auto && phrase = m_sourcePhrases[m_phraseToShow];
	for (auto i = 0; i < std::min(m_maxLineInPhrase, phrase.size()); ++i)
	{
		text.append(phrase[i]);
		text.append(1, L'\n');
	}

	m_text->setString(text);
}

void TextBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!m_isHidden)
	{
		UpdateText();
		states.transform.combine(getTransform());
		target.draw(m_background, states);
		target.draw(*m_text, states);	
	}
}

static const wchar_t *g_text = L"Ну привет, помнишь эту заправку? \
Я тогда впервые так близко посмотрел в твои глаза и даже не мог подумать, \
что они настолько мне понравятся. Я считаю, что мы ничтожно малое количество \
времени провели вместе, а я все так же хочу заглянуть тебе в душу. \
Я запомню твои ели заметные веснушки, которые по-настоящему прекрасны. \
Я думаю, ты прячешь их не лицом, а сердцем. Твой взгляд, который ты постоянно отводила, \
то ли от смущения, то ли от моей навязчивости, мне нравилось смотреть тебе в глаза. \
Ту ночь, когда ты уснула у меня на руках, смотря на звезды, знаешь, в тот момент \
я только хотел обнять тебя и остаться там навсегда. Все эти нелепые касания, это \
безумное желание взять тебя за руку, когда вместе едем в такси. На самом деле, \
очень печально, что все так получилось с вашим отъездом, мне было так мало времени \
с тобой. Помнишь, мы разговаривали о мечте, и я жалею, что из-за вашего отъезда, \
я не смог исполнить твою на это лето, а у меня было столько планов. \
Вышло очень забавно с цветами, я видел твой, изначально смущенный и удивленный \
взгляд, ведь ты подумала, что это я. Я же хочу оставить след не на столе в вазе, \
а в твоем маленьком сердце. Вот для чего я сделал это, я просто не могу молчать и \
отпустить тебя просто так. Ты спрашивала про сон, мне снилось, как я обнимал тебя, \
как прижимал к себе и как ты тянулась ко мне, и хоть в этом нет ничего такого, но это \
настолько притягивающее приятно, что я желал этого. Мне так мало тебя, \
каждый день мне хочется, быть ближе к тебе, каждый день, я хочу больше, \
хочу взять тебя за руку, хочу обнять тебя. Мне хочется просто говорить с тобой. \
Тогда, когда ты трогала мое сердце оно правда из-за этого билось очень сильно и \
это не пафос, а лишь показатель чего-то необычного и искреннего. И знаешь сейчас, \
когда я пишу это, я был бы готов быть с тобой и преодолеть любые трудности от расстояния, \
до, не понимая и непривычки, тебе лишь надо было сделать шаг на встречу. \
Меня почему-то тянет к тебе, ты очень красивая и дело тут не только во \
внешности, меня притягивают твои глаза, веснушки, твоя маленькая душа. \
Но все что я хотел, за это, казалось бы, не очень лето, несмотря на все \
обстоятельства, которые мешают, сдерживаю и ограничивают – это почувствовать \
твои губы… Я хочу, чтобы ты знала это…\
\
P.S. Я надеюсь ты не забудешь этого длинного мальчика, и мы с тобой сможем скоро встретится...\
\
P.P.S Я кое-что написал, найдешь в своих вещах";
