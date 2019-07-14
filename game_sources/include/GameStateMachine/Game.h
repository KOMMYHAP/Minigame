#pragma once

#include "GameStateMachine/GameScenesID.h"

class Application;
class GameScene;

class Game : public enable_shared_from_this<Game>
{
public:
	void Initialize(shared_ptr<Application> app);

	void RequestNextScene(GameScenes::Id id) { m_nextSceneId = id; }

	void UpdateScene(size_t dt);
	
	shared_ptr<GameScene> GetCurrentScene() const { return m_currentScene; }
	shared_ptr<GameScene> GetNextScene() const;

	sf::RenderWindow & GetRenderWindow();

private:
	void CheckAndSetNextScene();

	weak_ptr<Application>			m_application;

	map<GameScenes::Id, shared_ptr<GameScene>>		m_scenes;
	shared_ptr<GameScene>							m_currentScene;
	GameScenes::Id									m_nextSceneId {GameScenes::Id::SCENES_COUNT};
};