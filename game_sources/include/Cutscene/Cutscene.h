#pragma once

#include "General/GameScene.h"

class TextBox;
class Video;
class Character;

class Cutscene : public GameScene, public enable_shared_from_this<Cutscene>
{
public:
	Cutscene();

	void Initialize(shared_ptr<GameSceneCallback> callback);

	void OnStartScene() override;
	void OnEndScene() override;

	void ProcessInput() override;
	void Update(float dt) override;
	
	void Draw(sf::RenderWindow& window) override;

	shared_ptr<ResourceHandler> GetResources() const { return m_callback->GetResources(); }

private:
	vector<shared_ptr<Entity>>			m_entities;
	weak_ptr<Video>						m_background;
	
	shared_ptr<GameSceneCallback>		m_callback;
};
