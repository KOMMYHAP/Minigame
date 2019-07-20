#pragma once
#include "General/Entity.h"

class PlayField;

class HealthPack : public Entity
{
public:
	void Initialize(shared_ptr<PlayField> playfield);

	shared_ptr<PlayField> GetPlayfield() const { return m_playfield.lock(); }
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite					m_sprite;
	weak_ptr<PlayField>			m_playfield;
};
