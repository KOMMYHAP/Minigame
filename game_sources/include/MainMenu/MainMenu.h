#pragma once

#include "General/GameScene.h"

class MainMenu : public GameScene, public enable_shared_from_this<MainMenu>
{
public:
	void Initialize(shared_ptr<GameSceneCallback> callback);

	void OnStartScene() override;
	void OnEndScene() override;

	void ProcessInput() override;
	void Update(size_t dt) override;
	void Draw(sf::RenderWindow& window) override;

	shared_ptr<InputController> GetController() const { return m_callback->GetController(); }
	shared_ptr<ResourceHandler> GetResources() const { return m_callback->GetResources(); }

private:
	bool								m_isFirstShow {true};

	vector<shared_ptr<Entity>>			m_entities;
	shared_ptr<GameSceneCallback>		m_callback;
};
