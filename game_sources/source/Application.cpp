#include "stdafx_game.h"
#include "Application.h"

#include "LogMessageManager.h"
#include "InputController.h"

#include "GameStateMachine/Game.h"
#include "GameBasic/GameObjectManager.h"

Application::Application(int argc, char** argv)
	: m_videoMode(800, 600)
	, m_window(m_videoMode, "Snowfall", sf::Style::Close | sf::Style::Titlebar)
	, m_game(make_unique<Game>())
{
	m_window.setFramerateLimit(60);
	
	m_game->Initialize(shared_from_this());
}

int Application::Run()
{
	sf::Clock clock;

	while (m_window.isOpen())
	{
		InputController::Instance()->ProcessInput(m_window);

		if (InputController::Instance()->IsTryToShutdown())
		{
			// break down main loop or 
			// forward a signal into the Game to prevent user
			break;
		}

		clock.restart();

		auto dt = clock.getElapsedTime().asMilliseconds();
		while (dt > 0)
		{
			dt -= 17;
			m_game->UpdateScene(dt);
		}

		if (m_game->IsClosed())
		{
			break;
		}

		m_game->Draw(m_window);

		m_window.display();

	}

	return 0;
}

void Application::SingletonSequenceInitialize()
{
	m_singletonSequence.DeleteFirst(GameObjectManager::Instance());
	m_singletonSequence.DeleteLast(InputController::Instance());
	m_singletonSequence.DeleteLast(LogMessageManager::Instance());
}
