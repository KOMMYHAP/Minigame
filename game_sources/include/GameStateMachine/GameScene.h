#pragma once

class Game;

class GameScene : public sf::Drawable
{
public:
	virtual ~GameScene() = default;

	virtual void Initialize(shared_ptr<Game> game) = 0;

	virtual void Load() = 0;
	virtual void Unload() = 0;
	
	virtual void ProcessInput() = 0;
	virtual void Update(size_t dt) = 0;
};