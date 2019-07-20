#include "stdafx_game.h"

#include "GameField/ItemsHandler.h"

#include "GameField/HealthPack.h"
#include "GameField/Snowflake.h"
#include "GameField/Player.h"
#include "GameField/PlayField.h"

#include "General/ResourceHandler.h"
#include "BaseUtils.h"

ItemsHandler::ItemsHandler()
{

}

void ItemsHandler::Initialize(shared_ptr<PlayField> playfield, shared_ptr<Player> player)
{
	m_playfield = playfield;
	m_player= player;
	m_random = playfield->GetRandom();
}

void ItemsHandler::ProcessInput()
{
}

void ItemsHandler::Update(size_t dt)
{
	TryToCreateItem();

	while (!m_itemsToPlace.empty())
	{
		bool success = DoPlacingItem(m_itemsToPlace.back());
		if (!success)
		{
			break;
		}
	}

	decltype(m_items) toRemove;

	for (auto && item : m_items)
	{
		item->entity->Update(dt);

		if (TouchedPlayer(item))
		{
			toRemove.push_back(item);
			CallEvent(GameEvent::TOUCH_PLAYER, item->entity);
		} 
		else if (TouchedTheGround(item))
		{
			toRemove.push_back(item);
			CallEvent(GameEvent::TOUCH_GROUND, item->entity);
		}
	}

	while (!toRemove.empty())
	{
		auto && itemToRemove = toRemove.back();
		if (itemToRemove->type == Item::HEALTHPACK)
		{
			m_healthpackNumber -= 1;
		}
		else if (itemToRemove->type == Item::SNOWFLAKE)
		{
			m_snowflakeNumber -= 1;
		}

		BaseUtils::Remove(m_items, toRemove.back());
		toRemove.pop_back();
	}
}

sf::FloatRect ItemsHandler::GetBBox() const
{
	return {};
}

void ItemsHandler::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(getTransform());
	for (auto && item : m_items)
	{
		target.draw(*item->entity, states);
	}
}

void ItemsHandler::TryToCreateItem()
{
	ItemPtr item;

	if (m_snowflakeNumber < m_maxSnowflakeNumber)
	{
		item = make_shared<Item>();
		item->type = Item::SNOWFLAKE;

		auto snowflake = make_shared<Snowflake>();
		snowflake->Initialize(GetPlayfield());
		item->entity = std::move(snowflake);

		m_itemsToPlace.emplace_back(std::move(item));
		++m_snowflakeNumber;
	}

	if (m_healthpackNumber < m_maxHealthPackNumber)
	{
		item = make_shared<Item>();
		item->type = Item::HEALTHPACK;

		auto healthPack = make_shared<HealthPack>();
		healthPack->Initialize(GetPlayfield());
		item->entity = std::move(healthPack);

		m_itemsToPlace.emplace_back(std::move(item));
		++m_healthpackNumber;
	}
}

void ItemsHandler::CallEvent(GameEvent event, shared_ptr<Entity> sender)
{
	for (auto && listener : m_listeners)
	{
		listener->Call(event, sender);
	}
}

bool ItemsHandler::TouchedTheGround(ItemPtr item) const
{
	auto playfield = GetPlayfield();
	auto groundY = playfield->GetBBox().top + playfield->GetBBox().height;
	return item->entity->getPosition().y + item->entity->GetBBox().height / 2.0f >= groundY;
}

bool ItemsHandler::TouchedPlayer(ItemsHandler::ItemPtr item) const
{
	auto bbox = item->entity->GetBBox();
	auto player = GetPlayer()->GetBBox();
	return player.intersects(bbox);
}

bool ItemsHandler::DoPlacingItem(ItemPtr item)
{
	auto pos = GetFreePosition(item);
	if (pos != sf::Vector2f(-1, -1))
	{
		BaseUtils::Remove(m_itemsToPlace, item);
		item->entity->setPosition(pos);
		m_items.push_back(item);
		return true;
	}
	return false;
}

sf::Vector2f ItemsHandler::GetFreePosition(ItemPtr itemToPlace) const
{
	auto playfield = GetPlayfield();
	auto && playFieldBbox = playfield->GetBBox();
	auto && bbox = itemToPlace->entity->GetBBox();
	
	const float startX = playFieldBbox.left;
	const float endX = startX + playFieldBbox.width - bbox.width;
	const float stepX = bbox.width * 2;

	const float startY = playFieldBbox.top - playFieldBbox.height;
	const float endY = playFieldBbox.top;
	const float stepY = bbox.height;
	
	vector<sf::Vector2f> freePoses;

	for (float y = startY; y < endY; y += stepY)
	{
		for (float x = startX; x <= endX; x += stepX)
		{
			auto pos = sf::Vector2f(x, y);
			auto rightBottom = pos + sf::Vector2f(bbox.width, bbox.height);

			bool isContains = false;
			for (auto && item : m_items)
			{
				if (item->entity->GetBBox().contains(pos) || item->entity->GetBBox().contains(rightBottom))
				{
					isContains = true;
					break;
				}
			}

			if (!isContains)
			{
				freePoses.push_back(pos);
			}
		}
	}

	if (freePoses.empty())
	{
		return sf::Vector2f{-1, -1};	
	}

	std::uniform_int_distribution<size_t> getIndex(0, freePoses.size() - 1);
	auto index = getIndex(*m_random);
	assert(index >= 0 && index < freePoses.size());
	return freePoses[index];
}
