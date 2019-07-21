#include "stdafx_game.h"

#include "MainMenu/MainMenu.h"
#include "MainMenu/PushButton.h"
#include "General/GameScene.h"
#include "LogMessageManager.h"

void MainMenu::Initialize(shared_ptr<GameSceneCallback> callback)
{
	m_callback = callback;
}

void MainMenu::OnStartScene()
{
	LOG_MESSAGE("Scene [MainMenu] started.");

	if (m_isLoaded)
	{
		return;
	}
	
	auto start = make_shared<PushButton>();
	{
		auto buttonRect = sf::FloatRect(250, 350, 300, 100);
		start->Initialize(shared_from_this(), buttonRect);

		assert(GetResources()->LoadImage(Images::BUTTON_START, "Resources/start.png"));
		if (auto ptr = GetResources()->GetImage(Images::BUTTON_START))
		{
			start->SetImage(ptr);
		}

		start->SetOnClick([this]()
		{
			LOG_MESSAGE("Game started!");
			m_callback->RequireScene(GameScenes::PLAYFIELD);
		});	
		m_entities.push_back(start);
	}

	auto exit = make_shared<PushButton>();
	{
		auto buttonRect = sf::FloatRect(250, 450, 300, 100);
		exit->Initialize(shared_from_this(), buttonRect);
		
		assert(GetResources()->LoadImage(Images::BUTTON_EXIT, "Resources/exit.png"));
		if (auto ptr = GetResources()->GetImage(Images::BUTTON_EXIT))
		{
			exit->SetImage(ptr);
		}

		exit->SetOnClick([this]()
		{
			LOG_MESSAGE("Game exited!");
			m_callback->RequireQuitGame();
		});	
		m_entities.push_back(exit);
	}

	m_isLoaded = true;
}

void MainMenu::OnEndScene()
{
	LOG_MESSAGE("Scene [MainMenu] completed.");
}

void MainMenu::ProcessInput()
{
	for (auto && entity : m_entities)
	{
		entity->ProcessInput();
	}
}

void MainMenu::Update(float dt)
{
	for (auto && entity : m_entities)
	{
		entity->Update(dt);
	}
}

void MainMenu::Draw(sf::RenderWindow& window)
{
	sf::RenderStates states;
	for (auto && entity : m_entities)
	{
		window.draw(*entity, states);
	}
}