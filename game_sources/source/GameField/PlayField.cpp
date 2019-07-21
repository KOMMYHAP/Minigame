#include "stdafx_game.h"

#include "GameField/PlayField.h"
#include "GameField/Player.h"
#include "GameField/Snowflake.h"
#include "GameField/TopPanel.h"

#include "General/ResourceHandler.h"
#include "General/InputController.h"
#include "General/Video.h"

#include "LogMessageManager.h"
#include "GameField/HealthPack.h"
#include "GameField/ItemsHandler.h"

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
		case GameEvent::CUTSCENE_TRIGGER:
		{
			m_callback->RequireScene(GameScenes::CUTSCENE);
			LOG_MESSAGE("-----> YOU ARE WINNER! <-----");
			break;
		}
		default:
			assert(false);
			LOG_WARNING("ScorePanel send unknown event [%1%] to a PlayField", static_cast<size_t>(event));
			break;
		}	
	}

	if (auto healthPanel = std::dynamic_pointer_cast<HealthPanel>(sender))
	{
		switch (event)
		{
		case GameEvent::END_OF_LIFE:
			m_callback->RequireScene(GameScenes::MAIN_MENU);
			LOG_MESSAGE("-----> YOU ARE LOOSER! <-----");
			break;
		default:
			assert(false);
			LOG_WARNING("HealthPanel send unknown event [%1%] to a PlayField", static_cast<size_t>(event));
			break;
		}
	}
}

void PlayField::OnStartScene()
{
	LOG_MESSAGE("Scene [PlayField] started.");

	m_entities.clear();

	auto resources = m_callback->GetResources();
	auto window = m_callback->GetRenderWindow();

	auto background = make_shared<Video>();
	auto success = resources->LoadVideo(Videoes::PLAYFIELD_BACKGROUND, "Resources/game_background.mp4");
	assert(sucess);
	if (auto ptr = resources->GetVideo(Videoes::PLAYFIELD_BACKGROUND))
	{
		m_videoBackground = background;
		background->Initialize(ptr, true);
		background->SetSize(window->getSize());
		background->Play();
	}

	if (!resources->LoadMusic(Musics::PLAYFIELD, "Resources/playfield.ogg"))
	{
		LOG_ERROR("Music not found!");
	}
	if (auto ptr = resources->GetMusic(Musics::PLAYFIELD))
	{
		ptr->setLoop(true);
		ptr->play();
	}

	if (auto ptr = resources->GetDefaultTexture())
	{
		m_sprite = sf::Sprite(*ptr);
		m_sprite.setTextureRect({0, 0, int(window->getSize().x), int(window->getSize().y)});
	}

	auto player = make_shared<Player>();
	{
		player->Initialize(shared_from_this());
		auto && bbox = GetBBox();
		player->setPosition(bbox.left + bbox.width / 2.f - player->GetBBox().width / 2.f, bbox.top + bbox.height - player->GetBBox().height);
	}

	auto topPanel = make_shared<TopPanel>();
	{
		topPanel->Initialize(shared_from_this());
		topPanel->Subscribe(shared_from_this());
	}

	auto itemsHandler = make_shared<ItemsHandler>();
	{
		itemsHandler->Initialize(shared_from_this(), player);
		itemsHandler->SetMaximumSnowflakes(15);
		itemsHandler->SetMaximumHealthPack(1);
		itemsHandler->Subscribe(topPanel);	
	}
	
	m_entities.emplace_back(background);
	m_entities.emplace_back(itemsHandler);
	m_entities.emplace_back(player);
	m_entities.emplace_back(topPanel);
}

void PlayField::OnEndScene()
{
	LOG_MESSAGE("Scene [PlayField] completed.");
	if (auto ptr = GetResources()->GetMusic(Musics::PLAYFIELD))
	{
		ptr->stop();
	}
	if (auto video = m_videoBackground.lock())
	{
		video->Stop();
	}
}

void PlayField::ProcessInput()
{
	auto input = m_callback->GetController();

	if (input->IsJustPressed(sf::Keyboard::Escape))
	{
		m_callback->RequireScene(GameScenes::MAIN_MENU);
		return;
	}

	if (input->IsJustPressed(sf::Keyboard::P))
	{
		if (auto music = GetResources()->GetMusic(Musics::PLAYFIELD))
		{
			m_onPause ? music->play() : music->pause();
		}
		if (auto video = m_videoBackground.lock())
		{
			m_onPause ? video->Play() : video->Pause();	
		}

		m_onPause = !m_onPause;
	}

	for (auto && entity : m_entities)
	{
		entity->ProcessInput();
	}
}

void PlayField::Update(float dt)
{
	if (m_onPause)
	{
		return;
	}

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