#pragma once

#include "General/Entity.h"

enum class GameEvent;
class Player;
class PlayField;
class GameListener;

class Snowflake : public Entity
{
public:
	Snowflake();

	void Initialize(shared_ptr<PlayField> playfield);

	void Update(float dt) override;
	
	sf::FloatRect GetBBox() const override;

	shared_ptr<PlayField> GetPlayField() const { return m_playfield.lock(); }

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	// x offset helper
	struct Jitter
	{
		const float maxVelocity		{0.1f};		// velocity by the X axis
		const float maxOffset		{25.f};	// maximum offset by X axid
		float		offset			{0.0f};		// current offset by X axid, changed by update

	} m_jitter;

	float						m_velocityY {1.2f};
	const float					m_angularVelocity {0.5};

	sf::Vector2f				m_velocity;

	weak_ptr<PlayField>			m_playfield;
	sf::Sprite					m_sprite;

};