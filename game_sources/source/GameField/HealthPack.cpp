#include "stdafx_game.h"

#include "GameField/HealthPack.h"

#include "GameField/PlayField.h"
#include "General/ResourceHandler.h"

void HealthPack::Initialize(shared_ptr<PlayField> playfield)
{
	auto resources = playfield->GetResources();
	assert(resources->LoadImage(Images::BEER, "Resources/beer.png"));
	if (auto ptr = resources->GetImage(Images::BEER))
	{
		m_sprite.setTexture(*ptr);
		m_sprite.scale(0.2f, 0.2f);
	}
}

void HealthPack::Update(size_t dt)
{
	move(0, 1.3f);
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
