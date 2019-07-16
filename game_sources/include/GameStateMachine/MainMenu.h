#pragma once

#include "GameStateMachine/GameScene.h"

class GameObject;

class MainMenuScene : public GameScene
{
public:
	MainMenuScene();
	~MainMenuScene() override;

	void Initialize(shared_ptr<Game> game) override;

	void Load() override;
	void Unload() override;

	void Update(size_t dt) override;
	void ProcessInput() override;

	GameObject* GetGameObject() const override { return m_object; }

	bool IsReady() override;

private:
	shared_ptr<Game> GetGame() const { return m_game.lock(); }

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	weak_ptr<Game>				m_game;
	GameObject *				m_object {nullptr};

	vector<unique_ptr<Entity>>			m_entities;
	vector<unique_ptr<RenderEntity>>	m_graphicsEntities;
};