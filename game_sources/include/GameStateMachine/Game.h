#pragma once

#include "GameStateMachine/GameScenesID.h"

class Application;
class GameScene;
class GameObject;

class Game : public enable_shared_from_this<Game>
{
public:
	~Game();

	void Initialize(shared_ptr<Application> app);

	void ProcessInput();
	void UpdateScene(size_t dt);
	void Draw(sf::RenderTarget & target);

	bool IsClosed() const { return m_isClosed; }
	
	void RequestNextScene(GameScenes::Id id) { m_nextSceneId = id; }

	GameObject * GetRoot() { return m_root; }

private:
	shared_ptr<GameScene> GetCurrentScene() const { return m_currentScene.lock(); }
	void CheckAndSetNextScene();
	shared_ptr<GameScene> GetNextScene() const;

	weak_ptr<Application>							m_application;
	bool											m_isClosed {false};

	map<GameScenes::Id, shared_ptr<GameScene>>		m_scenes;
	weak_ptr<GameScene>								m_currentScene;
	GameScenes::Id									m_nextSceneId {GameScenes::Id::SCENES_COUNT};

	GameObject *									m_root {nullptr};
};