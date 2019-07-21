#pragma once
#include "General/Entity.h"

class GameListener;
class Player;
class PlayField;

class HealthPack : public Entity
{
public:
	void Initialize(shared_ptr<PlayField> playfield);

	shared_ptr<PlayField> GetPlayfield() const { return m_playfield.lock(); }

	void Update(float dt) override;

	sf::FloatRect GetBBox() const override;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Sprite					m_sprite;
	weak_ptr<PlayField>			m_playfield;
};
