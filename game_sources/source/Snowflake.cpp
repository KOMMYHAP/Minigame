#include "stdafx_game.h"

#include "Snowflake.h"

#include "PlayField.h"
#include "ResourceHandler.h"
#include "BaseUtils.h"
#include <ppltasks.h>

Snowflake::Snowflake()
{
}

void Snowflake::Initialize(shared_ptr<PlayField> playfield)
{
	m_playfield = playfield;

	auto resources = playfield->GetResources();

	bool success = resources->LoadImage(Images::SNOWFLAKE, "Resources/snowflake.png");
	assert(success);
	m_sprite = resources->GetImage(Images::SNOWFLAKE);
	
	m_velocity = {m_jitter.maxVelocity, m_velocityY};

	auto random = playfield->GetRandom();

	std::uniform_int_distribution<int> direction(0, 1);
	bool toLeft = direction(*random) == 1 ? true : false;
	m_velocity.x  *= toLeft ? -1.0f : 1.0f;
}

void Snowflake::Update(float dt)
{
	move(m_velocity);

	auto && playfieldBbox = GetPlayField()->GetBBox();
	auto && thisBbox = GetBBox();
	
	if (thisBbox.left <= playfieldBbox.left)
	{
		// setPosition(playfieldBbox.left + thisBbox.width / 4.0f, thisBbox.top);
		m_velocity.x = std::abs(m_velocity.x);
	}
	else if (thisBbox.left + thisBbox.width >= playfieldBbox.left + playfieldBbox.width)
	{
		// setPosition(playfieldBbox.left + playfieldBbox.width - thisBbox.width * 5.0f / 4.0f, thisBbox.top);
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
	
	m_sprite.rotate(m_angularVelocity);
}

sf::FloatRect Snowflake::GetBBox() const
{
	return getTransform().transformRect(m_sprite.getLocalBounds());
}

void Snowflake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(getTransform());
	target.draw(m_sprite, states);
}

// <----------------------   SnowflakeHandler   ----------------------------->

SnowflakeHandler::SnowflakeHandler()
{
}

void SnowflakeHandler::Initialize(shared_ptr<PlayField> playfield)
{
	m_playfield = playfield;
	m_random = playfield->GetRandom();
}

void SnowflakeHandler::ProcessInput()
{

}

void SnowflakeHandler::Update(float dt)
{
	TryToCreateSnowflake();

	for (auto && snowflake : m_snowflakesToPlace)
	{
		DoPlacingSnowflake(snowflake);
	}

	for (auto && snowflake : m_snowflakes)
	{
		snowflake->Update(dt);
	}

	RemovedDeadSnowflakes();
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

bool SnowflakeHandler::TouchedTheGround(shared_ptr<Snowflake> snowflake) const
{
	auto playfield = GetPlayfield();
	auto groundY = playfield->GetBBox().top + playfield->GetBBox().height;
	return snowflake->getPosition().y + snowflake->GetBBox().height >= groundY;
}

void SnowflakeHandler::RemovedDeadSnowflakes()
{
	for (auto it = m_snowflakes.begin(); it != m_snowflakes.end(); )
	{
		if (TouchedTheGround(*it))
		{
			it = m_snowflakes.erase(it);
		}
		else
		{
			++it;
		}
	}
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
