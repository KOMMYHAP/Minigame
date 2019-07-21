#pragma once

#include "General/GameScene.h"

class Cutscene : public GameScene
{
public:
	void Initialize(shared_ptr<GameSceneCallback> callback);

	void OnStartScene() override;
	void OnEndScene() override;

	void ProcessInput() override;
	void Update(float ms) override;
	
	void Draw(sf::RenderWindow& window) override;

private:
	bool								m_isLoaded {false};

	vector<shared_ptr<Entity>>			m_entities;
	
	shared_ptr<GameSceneCallback>		m_callback;
};
