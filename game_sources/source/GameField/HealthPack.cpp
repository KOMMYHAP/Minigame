#include "stdafx_game.h"

#include "GameField/HealthPack.h"

#include "GameField/PlayField.h"
#include "General/ResourceHandler.h"

void HealthPack::Initialize(shared_ptr<PlayField> playfield)
{
	auto resources = playfield->GetResources();
	auto random = playfield->GetRandom();

	auto success = resources->LoadImage(Images::BEER, "Resources/beer.png");
	assert(success);
	if (auto ptr = resources->GetImage(Images::BEER))
	{
		m_sprite.setTexture(*ptr);
		m_sprite.scale(0.14f, 0.14f);
	}
	
	std::uniform_int_distribution<int> direction(0, 1);
	bool toLeft = direction(*random) == 1 ? true : false;
	m_speedSettings.angularVelocity  *= toLeft ? -1.0f : 1.0f;
}

void HealthPack::Update(float dt)
{	
	auto angle = getRotation();
	if (angle >= 180.0f)
	{
		angle = angle - 360.0f;
	}

	if (abs(angle) >= m_speedSettings.maxAngle)
	{
		m_speedSettings.angularVelocity *= -1.0f;
	}

	sf::Vector2f stepVelocity = m_speedSettings.velocity * dt;
	float stepAngle = m_speedSettings.angularVelocity * dt;

	move(stepVelocity);
	rotate(stepAngle);
}

sf::FloatRect HealthPack::GetBBox() const
{
	return getTransform().transformRect(m_sprite.getGlobalBounds());
}

void HealthPack::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(getTransform());
	target.draw(m_sprite, states);
}
