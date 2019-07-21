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

		auto && glyph = ptr->getGlyph(L'�', fontSize, false);
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

static const wchar_t *g_text = L"�� ������, ������� ��� ��������? \
� ����� ������� ��� ������ ��������� � ���� ����� � ���� �� ��� ��������, \
��� ��� ��������� ��� ����������. � ������, ��� �� �������� ����� ���������� \
������� ������� ������, � � ��� ��� �� ���� ��������� ���� � ����. \
� ������� ���� ��� �������� ��������, ������� ��-���������� ���������. \
� �����, �� ������� �� �� �����, � �������. ���� ������, ������� �� ��������� ��������, \
�� �� �� ��������, �� �� �� ���� ������������, ��� ��������� �������� ���� � �����. \
�� ����, ����� �� ������ � ���� �� �����, ������ �� ������, ������, � ��� ������ \
� ������ ����� ������ ���� � �������� ��� ��������. ��� ��� ������� �������, ��� \
�������� ������� ����� ���� �� ����, ����� ������ ���� � �����. �� ����� ����, \
����� ��������, ��� ��� ��� ���������� � ����� ��������, ��� ���� ��� ���� ������� \
� �����. �������, �� ������������� � �����, � � �����, ��� ��-�� ������ �������, \
� �� ���� ��������� ���� �� ��� ����, � � ���� ���� ������� ������. \
����� ����� ������� � �������, � ����� ����, ���������� ��������� � ���������� \
������, ���� �� ��������, ��� ��� �. � �� ���� �������� ���� �� �� ����� � ����, \
� � ����� ��������� ������. ��� ��� ���� � ������ ���, � ������ �� ���� ������� � \
��������� ���� ������ ���. �� ���������� ��� ���, ��� �������, ��� � ������� ����, \
��� �������� � ���� � ��� �� �������� �� ���, � ���� � ���� ��� ������ ������, �� ��� \
��������� ������������� �������, ��� � ����� �����. ��� ��� ���� ����, \
������ ���� ��� �������, ���� ����� � ����, ������ ����, � ���� ������, \
���� ����� ���� �� ����, ���� ������ ����. ��� ������� ������ �������� � �����. \
�����, ����� �� ������� ��� ������ ��� ������ ��-�� ����� ������ ����� ������ � \
��� �� �����, � ���� ���������� ����-�� ���������� � ����������. � ������ ������, \
����� � ���� ���, � ��� �� ����� ���� � ����� � ���������� ����� ��������� �� ����������, \
��, �� ������� � ����������, ���� ���� ���� ���� ������� ��� �� �������. \
���� ������-�� ����� � ����, �� ����� �������� � ���� ��� �� ������ �� \
���������, ���� ����������� ���� �����, ��������, ���� ��������� ����. \
�� ��� ��� � �����, �� ���, �������� ��, �� ����� ����, �������� �� ��� \
��������������, ������� ������, ��������� � ������������ � ��� ������������� \
���� ����� � ����, ����� �� ����� ���\
\
P.S. � ������� �� �� �������� ����� �������� ��������, � �� � ����� ������ ����� ����������...\
\
P.P.S � ���-��� �������, ������� � ����� �����";
