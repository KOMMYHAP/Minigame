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

	void Update(size_t dt) override;
	
	sf::FloatRect GetBBox() const;

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

	float						m_velocityY {1.5f};
	const float					m_angularVelocity {0.5};

	sf::Vector2f				m_velocity;

	weak_ptr<PlayField>			m_playfield;
	sf::Sprite					m_sprite;

};

class SnowflakeHandler : public Entity
{
public:
	SnowflakeHandler();

	void Initialize(shared_ptr<PlayField> playfield, shared_ptr<Player> player);

	void ProcessInput() override;
	void Update(size_t dt) override;

	void SetMaximumSnowflakes(size_t number) { m_maxSnowflakeNumber = number; }
	void TryToCreateSnowflake();

	void Subscribe(shared_ptr<GameListener> listener) { m_listeners.emplace_back(std::move(listener)); }
	
	shared_ptr<PlayField> GetPlayfield() const { return m_playfield.lock(); }
	shared_ptr<Player> GetPlayer() const { return m_player.lock(); }

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void CallEvent(GameEvent event, shared_ptr<Entity> sender);
	bool TouchedTheGround(shared_ptr<Snowflake> snowflake) const;
	bool TouchedPlayer(shared_ptr<Snowflake> snowflake) const;

	void DoPlacingSnowflake(shared_ptr<Snowflake> snowflake);
	sf::Vector2f GetFreePosition(shared_ptr<Snowflake> snowflake) const;

	vector<shared_ptr<GameListener>>		m_listeners;

	size_t									m_maxSnowflakeNumber {0};
	vector<shared_ptr<Snowflake>>			m_snowflakes;
	vector<shared_ptr<Snowflake>>			m_snowflakesToPlace;
	
	shared_ptr<std::mt19937>				m_random;
	weak_ptr<PlayField>						m_playfield;
	weak_ptr<Player>						m_player;
};