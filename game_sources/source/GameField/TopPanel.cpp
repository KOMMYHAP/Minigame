#include "stdafx_game.h"

#include "GameField/TopPanel.h"
#include "GameField/PlayField.h"
#include "GameField/Snowflake.h"

#include "General/ResourceHandler.h"

#include "LogMessageManager.h"
#include "GameField/HealthPack.h"

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

		auto bbox = m_scores->GetBBox();

		sf::Vector2f pos = { 
			playfieldBbox.left + playfieldBbox.width - bbox.width - 20.0f, 
			playfieldBbox.top + 10.0f
		};
		m_scores->setPosition(pos);	
	}

	m_health = make_shared<HealthPanel>();
	{
		m_health->Initialize(playfield->GetResources());
		sf::Vector2f pos = { 
			playfieldBbox.left + 20.0f, 
			playfieldBbox.top + 10.0f
		};
		m_health->setPosition(pos);	
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
			m_health->OnMissingSnowlake();
			if (m_health->GetLifes() == 0)
			{
				CallEvent(GameEvent::END_OF_LIFE, m_health);
			}
			break;
		case GameEvent::TOUCH_PLAYER:
			m_scores->OnTouch();
			if (m_scores->IsEnoughScoresForWin())
			{
				CallEvent(GameEvent::CUTSCENE_TRIGGER, m_scores);	
			}
			break;
		default:
			LOG_WARNING("Snowflake send unknown event [%1%] to a TopPanel", static_cast<size_t>(event));
			break;
		}	
	}
	if (auto healthPack = std::dynamic_pointer_cast<HealthPack>(sender))
	{
		switch (event)
		{
		case GameEvent::TOUCH_PLAYER:
			m_health->OnTouchingHealthPack();
			break;
		default:
			LOG_WARNING("Snowflake send unknown event [%1%] to a TopPanel", static_cast<size_t>(event));
		}
	}
}

sf::FloatRect TopPanel::GetBBox() const
{
	return {};
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
	target.draw(*m_health, states);
}

// |------------------ HealthPanel -------------.
//												 \
//												 \/


HealthPanel::HealthPanel()
	: m_text(make_unique<sf::Text>())
{
}

void HealthPanel::Initialize(shared_ptr<ResourceHandler> resources)
{
	assert(resources->LoadFont(Fonts::DEFAULT, "Resources/16105.ttf"));
	if (auto ptr = resources->GetFont(Fonts::DEFAULT))
	{
		m_text->setFont(*ptr);
		m_text->setCharacterSize(50);
		m_text->setFillColor(sf::Color::White);
		m_text->setOutlineColor(sf::Color::Black);
		m_text->setPosition(60.0f, -20.0f);
	}

	assert(resources->LoadImage(Images::HEART, "Resources/heart.png"));
	if (auto ptr = resources->GetImage(Images::HEART))
	{
		m_sprite.setTexture(*ptr);
		m_sprite.scale(0.2f, 0.2f);
	}
}

void HealthPanel::OnMissingSnowlake()
{
	m_lifes = std::max(0, m_lifes - 1);
}

void HealthPanel::OnTouchingHealthPack()
{
	m_lifes = std::min(m_maxLifes, m_lifes + 1);
}

sf::FloatRect HealthPanel::GetBBox() const
{
	return getTransform().transformRect(m_sprite.getGlobalBounds());
}

void HealthPanel::UpdateText() const
{
	string buffer(250, 0);
	int n = std::snprintf(buffer.data(), buffer.size(), m_format, GetLifes());
	if (n > 0 && n < 250)
	{
		buffer.resize(n);
		m_text->setString(buffer);	
	}
}

void HealthPanel::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(getTransform());

	target.draw(m_sprite, states);

	UpdateText();
	target.draw(*m_text, states);
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

sf::FloatRect ScorePanel::GetBBox() const
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
