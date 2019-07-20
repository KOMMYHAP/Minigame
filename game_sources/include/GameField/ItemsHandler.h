#pragma once

#include "General/Entity.h"

class Snowflake;
enum class GameEvent;
class GameListener;
class Player;
class PlayField;

struct Item
{
	enum Type
	{
		HEALTHPACK, 
		SNOWFLAKE, 
		COUNT
	};

	shared_ptr<Entity>		entity;
	Type					type {COUNT}; 
};

class ItemsHandler : public Entity
{
public:
	ItemsHandler();

	void Initialize(shared_ptr<PlayField> playfield, shared_ptr<Player> player);

	void ProcessInput() override;
	void Update(size_t dt) override;
	
	void SetMaximumSnowflakes(size_t number) { m_maxSnowflakeNumber = number; }
	void SetMaximumHealthPack(size_t number) { m_maxHealthPackNumber = number; }

	void Subscribe(shared_ptr<GameListener> listener) { m_listeners.emplace_back(std::move(listener)); }
	
	shared_ptr<PlayField> GetPlayfield() const { return m_playfield.lock(); }
	shared_ptr<Player> GetPlayer() const { return m_player.lock(); }
	sf::FloatRect GetBBox() const override;

private:
	using ItemPtr = shared_ptr<Item>;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void CallEvent(GameEvent event, shared_ptr<Entity> sender);
	bool TouchedTheGround(ItemPtr item) const;
	bool TouchedPlayer(ItemPtr item) const;
	
	void TryToCreateItem();
	bool DoPlacingItem(ItemPtr item);
	sf::Vector2f GetFreePosition(ItemPtr item) const;

	vector<shared_ptr<GameListener>>		m_listeners;
	
	size_t									m_maxSnowflakeNumber	{0};
	size_t									m_maxHealthPackNumber	{0};
	size_t									m_snowflakeNumber		{0};
	size_t									m_healthpackNumber		{0};

	vector<ItemPtr>							m_items;
	vector<ItemPtr>							m_itemsToPlace;
	
	shared_ptr<std::mt19937>				m_random;
	weak_ptr<PlayField>						m_playfield;
	weak_ptr<Player>						m_player;
};