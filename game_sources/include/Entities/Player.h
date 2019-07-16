#pragma once

#include "Entities/Entity.h"

namespace Entities
{

class Player : public Entity
{
public:
	Player();
	~Player();

	void Initialize(GameObject * parent);

	void ProcessInput() override;
	void Update(size_t dt) override;

	GameObject * GetGameObject() const override { return m_object; }

private:
	using Action = function<void()>;

	enum class ActionTypes
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
		JUMP,
		IDLE,
		COUNT
	};

	array<Action, static_cast<size_t>(ActionTypes::COUNT)>	
										m_actions;
	Action								m_currentAction;
	sf::Vector2f						m_velocity;

	GameObject *						m_object {nullptr};

};

}
