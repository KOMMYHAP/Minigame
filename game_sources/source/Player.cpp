#include "stdafx_game.h"

#include "Player.h"
#include "PlayerField.h"

#include "ResourceHandler.h"
#include "InputController.h"

#include "LogMessageManager.h"

Player::Player()
	: m_maxVelocity(15.f, -20.f)
{
}

void Player::Initialize(shared_ptr<PlayerField> playerField)
{
	m_field = playerField;
	assert(LoadAll());
	m_sprite = GetPlayerField()->GetResources()->GetImage(Images::GIRL);
}

void Player::ProcessInput()
{
	auto input = GetPlayerField()->GetController();
	
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

	const auto spriteRect = GetSpriteSize();
	const auto bottomRightCorner = pos + sf::Vector2f(spriteRect.width, spriteRect.height);

	if (GetPlayerField()->IsInBorders(pos) && GetPlayerField()->IsInBorders(bottomRightCorner))
	{
		setPosition(pos);
	}
	else 
	{
		MoveToBorder(pos);
	}

	UpdateMoving();
	UpdateJump();
}

sf::FloatRect Player::GetSpriteSize() const
{
	return getTransform().transformRect(m_sprite.getLocalBounds());
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

void Player::MoveToBorder(const sf::Vector2f& invalidPos)
{
	auto && border = GetPlayerField()->GetBorder();

	auto spriteRect = GetSpriteSize();
	sf::Vector2f validPos = invalidPos;
	if (invalidPos.x <= border.left)
	{
		validPos.x = border.left;
	}
	else if (invalidPos.x + spriteRect.width >= border.left + border.width)
	{
		validPos.x = border.left + border.width - GetSpriteSize().width;
	}

	setPosition(validPos);
}

bool Player::LoadAll()
{
	auto resources = GetPlayerField()->GetResources();

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
