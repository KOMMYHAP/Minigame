#include "stdafx_game.h"
#include "Entities/Player.h"

#include "GameBasic/GameObject.h"
#include "GameBasic/GameObjectManager.h"

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
		if (m_object->)
	}

	void Player::ProcessInput()
	{

	}
}
