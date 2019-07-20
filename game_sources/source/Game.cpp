#include "stdafx_game.h"

#include "Game.h"
#include "General/InputController.h"
#include "General/ResourceHandler.h"

#include "GameField/PlayField.h"
#include "MainMenu/MainMenu.h"
#include "LogMessageManager.h"

Game::Game()
	: m_window(make_shared<sf::RenderWindow>())
	, m_input(make_shared<InputController>())
	, m_resources(make_shared<ResourceHandler>())
{
}

void Game::Initialize(int argc, char** argv)
{
	m_window->create(sf::VideoMode(800, 600), "Snowflake", sf::Style::Titlebar | sf::Style::Close);

	
	auto sceneCallback = make_shared<GameSceneCallback>();
	sceneCallback->Initialize(shared_from_this());

	auto menu = make_shared<MainMenu>();
	menu->Initialize(sceneCallback);
	m_scenes[GameScenes::MAIN_MENU] = menu;

	auto playfield = make_shared<PlayField>();
	playfield->Initialize(sceneCallback);
	m_scenes[GameScenes::PLAYFIELD] = playfield;

	SetNextScene(GameScenes::MAIN_MENU);
}

void Game::Run()
{
	const size_t msPerFrame = 17;
	int dt = 0;
	sf::Clock clock;

	shared_ptr<GameScene> scene;
	
    while (m_window->isOpen() && !m_needExit)
    {
		clock.restart();

        m_input->ProcessInput(m_window);

		if (m_input->IsWindowClosingRequired())
		{
			SetNeedExit();
		}

		if (m_isRequiredNextScene)
		{
			if (scene)
			{
				scene->OnEndScene();
			}
			scene = GetRequiredScene();
			scene->OnStartScene();
			m_isRequiredNextScene = false;
		}
		
		scene->ProcessInput();

		scene->Update(msPerFrame);
		while (dt >= msPerFrame)
		{
			scene->Update(msPerFrame);
			dt -= msPerFrame;
		}

        m_window->clear();
        scene->Draw(*m_window);
        m_window->display();
		
		dt += clock.getElapsedTime().asMilliseconds();
		if (dt < msPerFrame)
		{
			sf::sleep(sf::milliseconds(msPerFrame - dt));
		}
    }
}

void Game::SetNextScene(GameScenes::Id id)
{
	auto it = m_scenes.find(id);
	assert(it != m_scenes.end());
	if (it != m_scenes.end())
	{
		m_requiredScene = id;
		m_isRequiredNextScene = true;
	}
}

void Game::SetNeedExit()
{
	LOG_MESSAGE("Game will be closed soon!");
	m_needExit = true;
}

shared_ptr<GameScene> Game::GetRequiredScene() const
{
	return m_scenes.at(m_requiredScene);
}
