#include "stdafx_game.h"

#include "GameField/Snowflake.h"
#include "GameField/Player.h"
#include "GameField/PlayField.h"

#include "General/ResourceHandler.h"
#include "General/GameListener.h"

#include "BaseUtils.h"

Snowflake::Snowflake()
{
}

void Snowflake::Initialize(shared_ptr<PlayField> playfield)
{
	m_playfield = playfield;

	auto resources = playfield->GetResources();

	bool success = resources->LoadImage(Images::SNOWFLAKE, "Resources/snowflake.png");
	assert(success);
	if (auto ptr = resources->GetImage(Images::SNOWFLAKE))
	{
		m_sprite.setTexture(*ptr);	
	}
	
	m_velocity = {m_jitter.maxVelocity, m_velocityY};

	auto random = playfield->GetRandom();

	std::uniform_int_distribution<int> direction(0, 1);
	bool toLeft = direction(*random) == 1 ? true : false;
	m_velocity.x  *= toLeft ? -1.0f : 1.0f;
}

void Snowflake::Update(size_t dt)
{
	auto && playfieldBbox = GetPlayField()->GetBBox();
	
	auto nextBbox = GetBBox();
	nextBbox.left += m_velocity.x;
	nextBbox.top += m_velocity.y;

	if (nextBbox.left <= playfieldBbox.left)
	{
		m_velocity.x = std::abs(m_velocity.x);
	}
	else if (nextBbox.left + nextBbox.width >= playfieldBbox.left + playfieldBbox.width)
	{
		m_velocity.x = -std::abs(m_velocity.x);
	}
	else 
	{
		if (std::abs(m_jitter.offset) >= m_jitter.maxOffset)
		{
			m_velocity.x *= -1;
		}
		
		m_jitter.offset += m_velocity.x;
	}

	move(m_velocity);
	rotate(m_angularVelocity);
}

sf::FloatRect Snowflake::GetBBox() const
{
	return getTransform().transformRect(m_sprite.getGlobalBounds());
}

void Snowflake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(getTransform());
	target.draw(m_sprite, states);
}

// |------------- SnowflakeHandler -------------.
//												 \
//												 \/

SnowflakeHandler::SnowflakeHandler()
{
}

void SnowflakeHandler::Initialize(shared_ptr<PlayField> playfield, shared_ptr<Player> player)
{
	m_playfield = playfield;
	m_player= player;
	m_random = playfield->GetRandom();
}

void SnowflakeHandler::ProcessInput()
{

}

void SnowflakeHandler::Update(size_t dt)
{
	TryToCreateSnowflake();

	for (auto && snowflake : m_snowflakesToPlace)
	{
		DoPlacingSnowflake(snowflake);
	}

	decltype(m_snowflakes) toRemove;

	for (auto && snowflake : m_snowflakes)
	{
		snowflake->Update(dt);

		if (TouchedPlayer(snowflake))
		{
			toRemove.push_back(snowflake);
			CallEvent(GameEvent::TOUCH_PLAYER, snowflake);
		} 
		else if (TouchedTheGround(snowflake))
		{
			toRemove.push_back(snowflake);
			CallEvent(GameEvent::TOUCH_GROUND, snowflake);
		}
	}

	while (!toRemove.empty())
	{
		BaseUtils::Remove(m_snowflakes, toRemove.back());
		toRemove.pop_back();
	}
}

void SnowflakeHandler::TryToCreateSnowflake()
{
	if (m_snowflakes.size() + m_snowflakesToPlace.size() >= m_maxSnowflakeNumber)
	{
		return;
	}

	m_snowflakesToPlace.push_back(make_shared<Snowflake>());
	m_snowflakesToPlace.back()->Initialize(GetPlayfield());
}

void SnowflakeHandler::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(getTransform());
	for (auto && snowflake : m_snowflakes)
	{
		target.draw(*snowflake, states);
	}
}

void SnowflakeHandler::CallEvent(GameEvent event, shared_ptr<Entity> sender)
{
	for (auto && listener : m_listeners)
	{
		listener->Call(event, sender);
	}
}

bool SnowflakeHandler::TouchedTheGround(shared_ptr<Snowflake> snowflake) const
{
	auto playfield = GetPlayfield();
	auto groundY = playfield->GetBBox().top + playfield->GetBBox().height;
	return snowflake->getPosition().y + snowflake->GetBBox().height >= groundY;
}

bool SnowflakeHandler::TouchedPlayer(shared_ptr<Snowflake> snowflake) const
{
	auto bbox = snowflake->GetBBox();
	auto player = GetPlayer()->GetBBox();
	return player.intersects(bbox);
}

void SnowflakeHandler::DoPlacingSnowflake(shared_ptr<Snowflake> snowflake)
{
	auto pos = GetFreePosition(snowflake);
	if (pos != sf::Vector2f(-1, -1))
	{
		BaseUtils::Remove(m_snowflakesToPlace, snowflake);
		snowflake->setPosition(pos);
		m_snowflakes.push_back(snowflake);
	}
}

sf::Vector2f SnowflakeHandler::GetFreePosition(shared_ptr<Snowflake> snowflake) const
{
	auto playfield = GetPlayfield();
	auto && playFieldBbox = playfield->GetBBox();
	auto && bbox = snowflake->GetBBox();
	
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
			for (auto && _snowflake : m_snowflakes)
			{
				if (_snowflake->GetBBox().contains(pos) || _snowflake->GetBBox().contains(rightBottom))
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
