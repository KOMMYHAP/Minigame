#pragma once

#include "General/GameScene.h"

class PushButton;

class MainMenu : public GameScene, public enable_shared_from_this<MainMenu>
{
public:
	void Initialize(shared_ptr<GameSceneCallback> callback);

	void OnStartScene() override;
	void OnEndScene() override;

	void ProcessInput() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	shared_ptr<InputController> GetController() const { return m_callback->GetController(); }
	shared_ptr<ResourceHandler> GetResources() const { return m_callback->GetResources(); }

private:
	bool								m_isLoaded {false};

	vector<shared_ptr<Entity>>			m_entities;
	sf::Text							m_text;

	shared_ptr<GameSceneCallback>		m_callback;
};
