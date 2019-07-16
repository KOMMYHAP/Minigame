#include "stdafx_game.h"
#include "Entities/Player.h"

#include "GameBasic/GameObject.h"
#include "GameBasic/GameObjectManager.h"
#include "InputController.h"
#include "GameBasic/GameUtils.h"

namespace Entities
{
	constexpr float g_speedMinX {-10.0f};
	constexpr float g_speedMaxX {10.0f};
	constexpr float g_speedMinY {0.0f};
	constexpr float g_speedMaxY {10.0f};

	Player::Player()
		: m_velocity(0, 0)
	{
		m_actions[static_cast<size_t>(ActionTypes::LEFT)] = [this]()
		{
			m_velocity.x = g_speedMinX;
		};
		
		m_actions[static_cast<size_t>(ActionTypes::RIGHT)] = [this]()
		{
			m_velocity.x = g_speedMaxX;
		};
		
		m_actions[static_cast<size_t>(ActionTypes::UP)] = [this]()
		{
		};
		
		m_actions[static_cast<size_t>(ActionTypes::DOWN)] = [this]()
		{
		};
		
		m_actions[static_cast<size_t>(ActionTypes::JUMP)] = [this]()
		{
			if (m_velocity.y - g_speedMinY < 0.0005f)
			{
				m_velocity.y = g_speedMaxY;
			}
		};

		m_actions[static_cast<size_t>(ActionTypes::IDLE)] = [this]()
		{
			m_velocity *= 0.95f;
		};

		m_currentAction = m_actions[static_cast<size_t>(ActionTypes::IDLE)];	
	}

	Player::~Player()
	{
		if (!m_object->GetParent())
		{
			GameObjectManager::Instance()->Delete(m_object);
		}
	}

	void Player::Initialize(GameObject* parent)
	{
		m_object = GameObjectManager::Instance()->Create("player", parent);
	}

	void Player::ProcessInput()
	{
		auto isPressed = [](InputKey key)
		{
			return InputController::Instance()->IsPressed(key);
		};

		auto action = ActionTypes::IDLE;

		if (isPressed(InputKey::W) || isPressed(InputKey::ARROW_UP))
		{
			action = ActionTypes::UP;
		}
		else if (isPressed(InputKey::A) || isPressed(InputKey::ARROW_LEFT))
		{
			action = ActionTypes::LEFT;
		}
		else if (isPressed(InputKey::S) || isPressed(InputKey::ARROW_DOWN))
		{
			action = ActionTypes::DOWN;
		}
		else if (isPressed(InputKey::D) || isPressed(InputKey::ARROW_RIGHT))
		{
			action = ActionTypes::RIGHT;
		}

		m_currentAction = m_actions[static_cast<size_t>(action)];
	}

	void Player::Update(size_t dt)
	{
		auto ms = dt / 1000.0f;
		GameUtils::MoveObject(m_object, m_velocity * ms);
	}
}
