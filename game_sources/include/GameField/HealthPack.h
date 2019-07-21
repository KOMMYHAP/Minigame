#pragma once
#include "General/Entity.h"

class GameListener;
class Player;
class PlayField;

struct HealthPackSpeedSettings
{
	sf::Vector2f	velocity			{0.0f, 80.0f};
	float			angularVelocity		{10.0f};
	float			maxAngle			{30.0f};
};

class HealthPack : public Entity
{
public:
	void Initialize(shared_ptr<PlayField> playfield);
	
	void Update(float dt) override;

	void SetSpeedSettings(const HealthPackSpeedSettings & settings) { m_speedSettings = settings; }

	sf::FloatRect GetBBox() const override;

	shared_ptr<PlayField> GetPlayfield() const { return m_playfield.lock(); }

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	HealthPackSpeedSettings		m_speedSettings;

	sf::Sprite					m_sprite;
	weak_ptr<PlayField>			m_playfield;
};
