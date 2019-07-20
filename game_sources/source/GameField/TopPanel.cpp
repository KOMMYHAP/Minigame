#include "stdafx_game.h"

#include "GameField/TopPanel.h"
#include "GameField/PlayField.h"
#include "GameField/Snowflake.h"

#include "General/ResourceHandler.h"

#include "LogMessageManager.h"

TopPanel::TopPanel()
{
}

void TopPanel::Initialize(shared_ptr<PlayField> playfield)
{
	m_playfield = playfield;
	
	auto playfieldBbox = getTransform().transformRect(playfield->GetBBox());

	m_scores = make_shared<ScorePanel>();
	{
		m_scores->Initialize(playfield->GetResources());

		auto bbox = m_scores->GetBbox();

		sf::Vector2f pos = { 
			playfieldBbox.left + playfieldBbox.width - bbox.width - 20.0f, 
			playfieldBbox.top + 10.0f
		};
		m_scores->setPosition(pos);	
	}
}

void TopPanel::Call(GameEvent event, shared_ptr<Entity> sender)
{
	if (auto snowflake = std::dynamic_pointer_cast<Snowflake>(sender))
	{
		switch (event)
		{
		case GameEvent::TOUCH_GROUND:
			m_scores->OnMiss();
			LOG_MESSAGE("TopPanel: ground was touched -> -1 live!");
			break;
		case GameEvent::TOUCH_PLAYER:
			m_scores->OnTouch();
			CallEvent(GameEvent::MORE_SCORES, m_scores);
			break;
		default:
			LOG_WARNING("Snowflake send unknown event [%1%] to a TopPanel", static_cast<size_t>(event));
			break;
		}	
	}
}

void TopPanel::CallEvent(GameEvent event, shared_ptr<Entity> sender)
{
	for (auto && listener : m_listeners)
	{
		listener->Call(event, sender);
	}
}

void TopPanel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(getTransform());

	target.draw(*m_scores, states);
}

// |------------------- ScorePanel -------------.
//												 \
//												 \/

ScorePanel::ScorePanel()
	: m_text(make_unique<sf::Text>())
{
}

void ScorePanel::Initialize(shared_ptr<ResourceHandler> resources)
{
	assert(resources->LoadFont(Fonts::DEFAULT, "Resources/16105.ttf"));
	if (auto ptr = resources->GetFont(Fonts::DEFAULT))
	{
		m_text->setFont(*ptr);
		m_text->setCharacterSize(24);
		m_text->setFillColor(sf::Color::White);
		m_text->setOutlineColor(sf::Color::Black);
	}

	UpdateText();
}

void ScorePanel::OnMiss()
{
	m_numberInARow = 0;
}

void ScorePanel::OnTouch()
{
	++m_numberInARow;
	m_numberInARow = std::min(m_numberInARow, m_maxCoef);

	size_t bonus = m_minBonus;
	bonus *= GetCurrentCoef();

	m_number += bonus;
	m_number = std::min(m_number, m_maxNumber);
}

sf::FloatRect ScorePanel::GetBbox() const
{
	return getTransform().transformRect(m_text->getGlobalBounds());
}

void ScorePanel::UpdateText() const
{
	string buffer(250, 0);
	int n = std::snprintf(buffer.data(), buffer.size(), m_format, GetScores(), GetCurrentCoef());
	if (n > 0 && n < 250)
	{
		buffer.resize(n);
		m_text->setString(buffer);	
	}
}

void ScorePanel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(getTransform());
	UpdateText();
	target.draw(*m_text, states);
}
