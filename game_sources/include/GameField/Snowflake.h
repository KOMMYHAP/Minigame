#pragma once

#include "General/Entity.h"

enum class GameEvent;
class Player;
class PlayField;
class GameListener;

struct SnowflakeSpeedSettings
{
	// x offset helper
	struct Jitter
	{
		float		velocityX		{6.0f};		// velocity by the X axis
		float		maxOffset		{25.f};		// maximum offset by X axid
		float		offset			{0.0f};		// current offset by X axid, changed by update

	} jitter;
	
	float			velocityY		{60.0f};
	float			angularVelocity	{30.0f};
};

class Snowflake : public Entity
{
public:
	Snowflake();

	void Initialize(shared_ptr<PlayField> playfield);

	void SetSpeedSettings(const SnowflakeSpeedSettings & settings) { m_speedSettings = settings;}

	void Update(float dt) override;
	
	sf::FloatRect GetBBox() const override;

	shared_ptr<PlayField> GetPlayField() const { return m_playfield.lock(); }

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	SnowflakeSpeedSettings		m_speedSettings;

	sf::Vector2f				m_velocity;

	weak_ptr<PlayField>			m_playfield;
	sf::Sprite					m_sprite;

};