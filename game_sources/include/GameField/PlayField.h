#pragma once

// #include "General/Entity.h"
#include "General/GameListener.h"
#include "General/GameScene.h"

class Entity;
class Player;
class SnowflakeHandler;

class PlayField : public GameScene, public GameListener, public enable_shared_from_this<PlayField>
{
public:
	using Action = function<void()>;
	enum class Event
	{
		SNOWFLAKE_TOUCHED,
		SNOWFLAKE_MISSED,
		COUNT
	};

	PlayField();
	~PlayField();

	void Initialize(shared_ptr<GameSceneCallback> callback);

	void OnStartScene() override;
	void OnEndScene() override;

	void ProcessInput() override;
	void Update(size_t dt) override;
	void Draw(sf::RenderWindow& window) override;
	
	void Call(GameEvent event, shared_ptr<Entity> sender) override;

	sf::FloatRect GetBBox() const;
	
	shared_ptr<InputController> GetController() const { return m_callback->GetController(); }
	shared_ptr<ResourceHandler> GetResources() const { return m_callback->GetResources(); }
	shared_ptr<std::mt19937>	GetRandom() const { return m_random; }

private:
	size_t								m_scoresToWin {99999};

	map<Event, vector<Action>>			m_actions;
	vector<shared_ptr<Entity>>			m_entities;

	bool								m_onPause {false};
	sf::Sprite							m_sprite;

	shared_ptr<std::mt19937>			m_random;
	shared_ptr<GameSceneCallback>		m_callback;
};
