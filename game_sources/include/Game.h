#pragma once
#include "General/GameScene.h"

class ResourceHandler;
class InputController;
class Entity;

class Game : public enable_shared_from_this<Game>
{
	friend class GameSceneCallback;
public:
	Game();

	void Initialize(int argc, char **argv);
	void Run();
	
	shared_ptr<InputController> GetController() const { return m_input; }
	shared_ptr<ResourceHandler> GetResources() const { return m_resources; }
	shared_ptr<sf::RenderWindow> GetRenderWindow() const { return m_window; }
	
	void SetNextScene(GameScenes::Id id);
	void SetNeedExit();
	
private:
	shared_ptr<GameScene> GetRequiredScene() const;

	map<GameScenes::Id, shared_ptr<GameScene>>	m_scenes;
	GameScenes::Id								m_requiredScene {GameScenes::MAIN_MENU};

	bool										m_isRequiredNextScene {true};
	bool										m_needExit {false};

	shared_ptr<sf::RenderWindow>				m_window;
	shared_ptr<InputController>					m_input;
	shared_ptr<ResourceHandler>					m_resources;
};
