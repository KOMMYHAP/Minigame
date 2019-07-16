#include "stdafx_gamelib.h"

#include "GameBasic/GameObject.h"
#include "GameBasic/GameObjectManager.h"

#include "GameStateMachine/Game.h"
#include "GameStateMachine/MainMenu.h"

#include "InputController.h"

Game::~Game()
{
	GameObjectManager::Instance()->Delete(m_root);
}

void Game::Initialize()
{
	m_root = GameObjectManager::Instance()->Create("game_root", nullptr);

	auto mainMenuScene = make_shared<MainMenuScene>();
	mainMenuScene->Initialize(shared_from_this());
	m_scenes.emplace(GameScenes::Id::MAIN_MENU, move(mainMenuScene));

	m_nextSceneId = GameScenes::Id::MAIN_MENU;
}

void Game::ProcessInput()
{
	if (InputController::Instance()->IsPressed(InputKey::ESC))
	{
		m_isClosed = true;
	}
}

void Game::UpdateScene(size_t dt)
{
	if (m_isClosed)
	{
		return;
	}

	CheckAndSetNextScene();

	if (auto scene = GetCurrentScene())
	{
		scene->Update(dt);
	}
}

void Game::Draw(sf::RenderTarget & target)
{
	if (auto scene = GetCurrentScene())
	{
		target.draw(*scene.get(), m_root->GetGeometry());
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

void Game::CheckAndSetNextScene()
{
	if (m_nextSceneId != GameScenes::Id::SCENES_COUNT)
	{
		if (auto scene = GetCurrentScene())
		{
			scene->Unload();
		}

		auto nextScene = GetNextScene();
		nextScene->Load();

		m_currentScene = nextScene;
		m_nextSceneId = GameScenes::Id::SCENES_COUNT;
	}
}
