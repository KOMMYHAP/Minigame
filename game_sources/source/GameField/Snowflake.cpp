#include "stdafx_game.h"

#include "GameField/Snowflake.h"
#include "GameField/Player.h"
#include "GameField/PlayField.h"

#include "General/ResourceHandler.h"
#include "General/GameListener.h"

#include "BaseUtils.h"

Snowflake::Snowflake()
{
}

void Snowflake::Initialize(shared_ptr<PlayField> playfield)
{
	m_playfield = playfield;

	auto resources = playfield->GetResources();

	bool success = resources->LoadImage(Images::SNOWFLAKE, "Resources/snowflake.png");
	assert(success);
	if (auto ptr = resources->GetImage(Images::SNOWFLAKE))
	{
		m_sprite.setTexture(*ptr);	
	}
	
	m_velocity = {m_speedSettings.jitter.velocityX, m_speedSettings.velocityY};

	auto random = playfield->GetRandom();

	std::uniform_int_distribution<int> direction(0, 1);
	bool toLeft = direction(*random) == 1 ? true : false;
	m_velocity.x  *= toLeft ? -1.0f : 1.0f;
}

void Snowflake::Update(float dt)
{
	auto && playfieldBbox = GetPlayField()->GetBBox();
	auto nextBbox = GetBBox();
	auto step = m_velocity * dt;
	nextBbox.left += step.x;
	nextBbox.top += step.y;

	if (nextBbox.left <= playfieldBbox.left)
	{
		m_velocity.x = std::abs(m_velocity.x);
	}
	else if (nextBbox.left + nextBbox.width >= playfieldBbox.left + playfieldBbox.width)
	{
		m_velocity.x = -std::abs(m_velocity.x);
	}
	else 
	{
		if (std::abs(m_speedSettings.jitter.offset) >= m_speedSettings.jitter.maxOffset)
		{
			m_velocity.x *= -1;
		}
		
		m_speedSettings.jitter.offset += m_velocity.x;
	}

	move(step);
	rotate(m_speedSettings.angularVelocity * dt);
}

sf::FloatRect Snowflake::GetBBox() const
{
	return getTransform().transformRect(m_sprite.getGlobalBounds());
}

void Snowflake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(getTransform());
	target.draw(m_sprite, states);
}
