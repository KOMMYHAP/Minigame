#pragma once

#include "GameStateMachine/GameScene.h"

class GameObject;
class Entity;

class MainMenuScene : public GameScene
{
public:
	~MainMenuScene() override;

	void Initialize(shared_ptr<Game> game) override;

	void Load() override;
	void Unload() override;

	void Update(size_t dt) override;
	void ProcessInput() override;

private:
	shared_ptr<Game> GetGame() const { return m_game.lock(); }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	weak_ptr<Game>				m_game;
	GameObject *				m_parent {nullptr};
	vector<unique_ptr<Entity>>	m_entities;
};