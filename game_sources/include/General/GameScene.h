#pragma once

class InputController;
class ResourceHandler;
class Game;
class Entity;

namespace GameScenes
{
	enum Id
	{
		MAIN_MENU,
		PLAYFIELD,
		// CUTSCENE,
		COUNT
	};
}

class GameSceneCallback
{
public:
	void Initialize(shared_ptr<Game> game) { m_game = game; }
	
	shared_ptr<InputController> GetController() const;
	shared_ptr<ResourceHandler> GetResources() const;
	shared_ptr<sf::RenderWindow> GetRenderWindow() const;

	void RequireScene(GameScenes::Id id) const;
	void RequireQuitGame() const;

private:
	shared_ptr<Game> GetGame() const { return m_game.lock(); }

	weak_ptr<Game>					m_game;
};

class GameScene
{
public:
	virtual ~GameScene() = default;
	
	virtual void OnStartScene() = 0;
	virtual void OnEndScene() = 0;

	virtual void ProcessInput() = 0;
	virtual void Update(size_t ms) = 0;
	virtual void Draw(sf::RenderWindow & window) = 0;
};