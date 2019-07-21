#include "stdafx_game.h"

#include "GameField/Player.h"
#include "GameField/PlayField.h"

#include "General/ResourceHandler.h"
#include "General/InputController.h"

#include "LogMessageManager.h"

Player::Player()
{
}

void Player::Initialize(shared_ptr<PlayField> playField)
{
	m_field = playField;
	assert(LoadAll());
	if (auto ptr = GetPlayField()->GetResources()->GetImage(Images::GIRL))
	{
		m_sprite.setTexture(*ptr);
		m_sprite.setScale(0.20f, 0.20f);
	}
}

void Player::ProcessInput()
{
	auto input = GetPlayField()->GetController();
	
	if (input->IsKeyDown(sf::Keyboard::W) || input->IsKeyDown(sf::Keyboard::Up) || input->IsKeyDown(sf::Keyboard::Space))
	{
		if (!m_jump)
		{
			CreateJump();	
		}
	}
	
	if (input->IsKeyDown(sf::Keyboard::A) || input->IsKeyDown(sf::Keyboard::Left))
	{
		m_velocity.x = -m_initialVelocity.x;
	}
	else if (input->IsKeyDown(sf::Keyboard::D) || input->IsKeyDown(sf::Keyboard::Right))
	{
		m_velocity.x = m_initialVelocity.x;	
	}
	
}

void Player::Update(float dt)
{	
	sf::Vector2f step = m_velocity * dt;

	auto && playfieldRect = GetPlayField()->GetBBox();

	auto nextBbox = GetBBox();
	nextBbox.left += step.x;
	nextBbox.top += step.y;

	if (nextBbox.left <= playfieldRect.left)
	{
		setPosition(playfieldRect.left, nextBbox.top);
	}
	else if (nextBbox.left + nextBbox.width >= playfieldRect.left + playfieldRect.width)
	{	
		setPosition(playfieldRect.left + playfieldRect.width - nextBbox.width, nextBbox.top);
	}
	else
	{
		move(step);	
	}

	UpdateMoving(dt);
	UpdateJump(dt);
}

sf::FloatRect Player::GetBBox() const
{
	return getTransform().transformRect(m_sprite.getGlobalBounds());
}

void Player::CreateJump()
{
	m_jump = make_unique<JumpHelper>();
	m_jump->startY = getPosition().y;
	m_jump->endY = m_jump->startY - m_jump->jumpHeight;
	m_velocity.y = m_initialVelocity.y;
}

void Player::UpdateJump(float dt)
{
	if (m_jump)
	{
		if (m_jump->isFlyingUp)
		{
			m_velocity.y -= m_jump->acceleraionUp * dt;
			m_velocity.y = std::max(m_velocity.y, (m_jump->endY - getPosition().y) / dt);

			if (getPosition().y <= m_jump->endY)
			{
				m_jump->isFlyingUp = false;
				m_velocity.y = 0.0f;
			}
		}
		else
		{
			m_velocity.y += m_jump->acceleraionDown * dt;
			m_velocity.y = std::min(m_velocity.y,  (m_jump->startY - getPosition().y) / dt);

			if (getPosition().y >= m_jump->startY)
			{
				m_jump.reset();
			}
		}
	}
}

void Player::UpdateMoving(float dt)
{
	m_velocity.x *= 0.5;
	if (std::abs(m_velocity.x) < 30.0f)
	{
		m_velocity.x = 0.0;
	}
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
