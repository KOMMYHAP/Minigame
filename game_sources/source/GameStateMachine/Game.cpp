#include "stdafx_gamelib.h"

#include "GameStateMachine/Game.h"
#include "GameStateMachine/MainMenu.h"
#include "Application.h"

void Game::Initialize(shared_ptr<Application> app)
{
	m_application = app;

	auto mainMenuScene = make_shared<MainMenuScene>();
	mainMenuScene->Initialize(shared_from_this());
	m_scenes.emplace(GameScenes::Id::MAIN_MENU, move(mainMenuScene));
}

void Game::UpdateScene(size_t dt)
{
	CheckAndSetNextScene();

	if (m_currentScene)
	{
		m_currentScene->Update(dt);
	}
}

shared_ptr<GameScene> Game::GetNextScene() const
{
	auto it = m_scenes.find(m_nextSceneId);
	if (it != m_scenes.end())
	{
		return it->second;
	}
	return nullptr;
}

sf::RenderWindow& Game::GetRenderWindow()
{
	if (auto app = m_application.lock())
	{
		return app->GetRenderWindow();
	}

	static sf::RenderWindow w;
	return w;
}

void Game::CheckAndSetNextScene()
{
	if (m_nextSceneId != GameScenes::Id::SCENES_COUNT)
	{
		m_currentScene->Unload();

		auto nextScene = GetNextScene();
		nextScene->Initialize(shared_from_this());
		nextScene->Load();

		m_currentScene = nextScene;
		m_nextSceneId = GameScenes::Id::SCENES_COUNT;
	}
}
