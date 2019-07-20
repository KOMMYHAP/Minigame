#pragma once

#include "General/Entity.h"
#include "General/GameListener.h"

class Player;
class SnowflakeHandler;

class PlayField : public Entity, public GameListener, public enable_shared_from_this<PlayField>
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

	void Initialize(shared_ptr<InputController> controller, shared_ptr<ResourceHandler> resources, shared_ptr<sf::Window> window);

	void Call(GameEvent event, shared_ptr<Entity> sender) override;

	void ProcessInput() override;
	void Update(size_t dt) override;

	sf::FloatRect GetBBox() const;
	
	shared_ptr<InputController> GetController() const { return m_input.lock(); }
	shared_ptr<ResourceHandler> GetResources() const { return m_resources.lock(); }
	shared_ptr<std::mt19937>	GetRandom() const { return m_random; }

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	size_t								m_scoresToWin {99999};

	map<Event, vector<Action>>			m_actions;
	vector<shared_ptr<Entity>>			m_entities;

	sf::Sprite							m_sprite;

	shared_ptr<std::mt19937>			m_random;
	weak_ptr<InputController>			m_input;
	weak_ptr<ResourceHandler>			m_resources;
};
