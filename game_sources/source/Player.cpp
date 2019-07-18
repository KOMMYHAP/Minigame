#include "stdafx_game.h"

#include "Player.h"
#include "PlayField.h"

#include "ResourceHandler.h"
#include "InputController.h"

#include "LogMessageManager.h"

Player::Player()
	: m_maxVelocity(15.f, -20.f)
{
}

void Player::Initialize(shared_ptr<PlayField> playField)
{
	m_field = playField;
	assert(LoadAll());
	m_sprite = GetPlayField()->GetResources()->GetImage(Images::GIRL);
}

void Player::ProcessInput()
{
	auto input = GetPlayField()->GetController();
	
	if (input->IsPressed(sf::Keyboard::W) || input->IsPressed(sf::Keyboard::Up) || input->IsPressed(sf::Keyboard::Space))
	{
		CreateJump();	
	}
	
	if (input->IsPressed(sf::Keyboard::A) || input->IsPressed(sf::Keyboard::Left))
	{
		m_velocity.x = -m_maxVelocity.x;
	}
	else if (input->IsPressed(sf::Keyboard::D) || input->IsPressed(sf::Keyboard::Right))
	{
		m_velocity.x = m_maxVelocity.x;	
	}
	
}

void Player::Update(float dt)
{	
	auto pos = getPosition() + m_velocity;

	auto && playerRect = GetBBox();
	auto && playfieldRect = GetPlayField()->GetBBox();
	
	auto p1 = sf::Vector2f(playerRect.left, playerRect.top);
	auto p2 = sf::Vector2f(playerRect.width + p1.x - 0.01f, playerRect.height + p1.y - 0.01f);

	if (playfieldRect.contains(p1) && playfieldRect.contains(p2))
	{
		setPosition(pos);
	}
	else 
	{
		auto && correctedPos = GetPlayField()->MoveToHorizontalBorder(playerRect);
		setPosition(correctedPos);
	}

	UpdateMoving();
	UpdateJump();
}

sf::FloatRect Player::GetBBox() const
{
	return getTransform().transformRect(m_sprite.getGlobalBounds());
}

void Player::CreateJump()
{
	if (!m_jump)
	{
		m_jump = make_unique<JumpHelper>();

		m_jump->startY = getPosition().y;
		m_jump->endY = m_jump->startY - m_jump->m_jumpHeight;
		m_velocity.y = m_maxVelocity.y;
	}
}

void Player::UpdateJump()
{
	if (m_jump)
	{
		if (m_jump->isFlyingUp)
		{
			m_velocity.y = std::min(m_velocity.y * m_jump->upCoef, -5.0f);
			m_velocity.y = std::max(m_velocity.y, m_jump->endY - getPosition().y);

			if (getPosition().y <= m_jump->endY)
			{
				m_jump->isFlyingUp = false;
				m_velocity.y = m_jump->initFlyingDownSpeed;
			}
		}
		else
		{
			m_velocity.y *= m_jump->downCoef;
			m_velocity.y = std::min(m_velocity.y,  m_jump->startY - getPosition().y);

			if (getPosition().y >= m_jump->startY)
			{
				m_jump.reset();
			}
		}
	}
}

void Player::UpdateMoving()
{
	m_velocity.x *= 0.5f;
}

bool Player::LoadAll()
{
	auto resources = GetPlayField()->GetResources();

	bool success = true;

	success &= resources->LoadImage(Images::GIRL, "Resources/girl.png");

	if (!success)
	{
		LOG_ERROR("Cannot load player resources!");
	}

	return success;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(getTransform());
	target.draw(m_sprite, states);
}
