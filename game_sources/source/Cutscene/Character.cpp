#include "stdafx_game.h"

#include "Cutscene/Character.h"
#include "Cutscene/Cutscene.h"

#include "General/ResourceHandler.h"

Character::Character()
{
}

void Character::Initialize(shared_ptr<ResourceHandler> resources)
{
	auto success = resources->LoadImage(Images::BOY, "Resources/boy.png");
	assert(success);
	if (auto ptr = resources->GetImage(Images::BOY))
	{
		m_sprite.setTexture(*ptr);
		m_sprite.setScale(0.25f, 0.25f);
	}
	setPosition(m_startPos);
}

void Character::Update(float dt)
{
	if (m_dt >= m_timeToMove)
	{
		return;
	}

	auto angle = getRotation();
	if (angle >= 180.0f)
	{
		angle = angle - 360.0f;
	}

	if (abs(angle) >= m_maxAngle)
	{
		m_angularVelocity *= -1.0f;
	}

	sf::Vector2f stepVelocity = m_velocity * dt;
	float stepAngle = m_angularVelocity * dt;
	float stepScale = (m_endScale - m_startScale) * dt;

	move(stepVelocity);
	rotate(stepAngle);
	
	m_dt += dt;
	if (m_dt >= m_timeToMove)
	{
		CallAll(GameEvent::CUTSCENE_CHARACTER_MOVING_COMPLETED, shared_from_this());
	}
	
	setScale(m_scale, m_scale);
	m_scale += stepScale;
}

sf::FloatRect Character::GetBBox() const
{
	return getTransform().transformRect(m_sprite.getGlobalBounds());
}

void Character::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(getTransform());
	target.draw(m_sprite, states);
}

void Character::CallAll(GameEvent event, shared_ptr<Entity> sender) const
{
	for (auto && listener : m_listeners)
	{
		listener->Call(event, sender);
	}
}
