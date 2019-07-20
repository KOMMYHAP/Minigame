#include "stdafx_game.h"

#include "GameField/PlayField.h"
#include "GameField/Player.h"
#include "GameField/Snowflake.h"
#include "GameField/TopPanel.h"

#include "General/ResourceHandler.h"

#include "LogMessageManager.h"

PlayField::PlayField()
	: m_random(make_shared<std::mt19937>())
{
}

PlayField::~PlayField()
{
	
}

void PlayField::Initialize(shared_ptr<GameSceneCallback> callback)
{
	m_callback = callback;
}

void PlayField::Call(GameEvent event, shared_ptr<Entity> sender)
{
	if (auto scorePanel = std::dynamic_pointer_cast<ScorePanel>(sender))
	{
		switch (event)
		{
		case GameEvent::MORE_SCORES:
		{
			auto scores = scorePanel->GetScores();
			if (scores >= m_scoresToWin)
			{
				m_callback->RequireScene(GameScenes::MAIN_MENU);
				LOG_MESSAGE("-----> YOU ARE WINNER! <-----");
			}
			break;
		}
		default:
			LOG_WARNING("ScorePanel send unknown event [%1%] to a PlayField", static_cast<size_t>(event));
			break;
		}	
	}
}

void PlayField::OnStartScene()
{
	LOG_MESSAGE("Scene [PlayField] started.");
	if (m_isLoaded)
	{
		if (auto ptr = GetResources()->GetMusic(Music::PLAYFIELD))
		{
			ptr->play();
		}

		return;
	}

	auto resources = m_callback->GetResources();
	auto window = m_callback->GetRenderWindow();

	resources->LoadMusic(Music::PLAYFIELD, "Resources/test.ogg");
	if (auto ptr = resources->GetMusic(Music::PLAYFIELD))
	{
		ptr->setLoop(true);
		ptr->play();
	}

	if (auto ptr = resources->GetDefaultTexture())
	{
		m_sprite = sf::Sprite(*ptr);
		m_sprite.setTextureRect({0, 0, int(window->getSize().x), int(window->getSize().y)});
	}

	auto && bbox = GetBBox();

	auto player = make_shared<Player>();
	{
		player->Initialize(shared_from_this());		
		player->setPosition(bbox.left + bbox.width / 2.f - player->GetBBox().width / 2.f, bbox.top + bbox.height - player->GetBBox().height);
		m_entities.emplace_back(player);
	}

	auto topPanel = make_shared<TopPanel>();
	{
		topPanel->Initialize(shared_from_this());
		topPanel->Subscribe(shared_from_this());
		m_entities.emplace_back(topPanel);
	}

	auto snowflakeHandler = make_shared<SnowflakeHandler>();
	{
		snowflakeHandler->Initialize(shared_from_this(), player);
		snowflakeHandler->SetMaximumSnoflakes(10);
		snowflakeHandler->Subscribe(topPanel);
		m_entities.emplace_back(snowflakeHandler);
	}

	m_isLoaded = true;
}

void PlayField::OnEndScene()
{
	LOG_MESSAGE("Scene [PlayField] completed.");
	if (auto ptr = GetResources()->GetMusic(Music::PLAYFIELD))
	{
		ptr->pause();
	}
}

void PlayField::ProcessInput()
{
	for (auto && entity : m_entities)
	{
		entity->ProcessInput();
	}
}

void PlayField::Update(size_t dt)
{
	for (auto && entity : m_entities)
	{
		entity->Update(dt);
	}
}

void PlayField::Draw(sf::RenderWindow& window)
{
	sf::RenderStates states;
	for (auto && entity : m_entities)
	{
		window.draw(*entity, states);
	}
}

sf::FloatRect PlayField::GetBBox() const
{
	return m_sprite.getGlobalBounds();
}