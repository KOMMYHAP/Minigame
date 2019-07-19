#include "stdafx_game.h"

#include "PlayField.h"

#include "ResourceHandler.h"
#include "Player.h"
#include "Snowflake.h"

PlayField::PlayField()
	: m_random(make_shared<std::mt19937>())
{
}

void PlayField::Initialize(shared_ptr<InputController> controller, shared_ptr<ResourceHandler> resources, shared_ptr<sf::Window> window)
{
	m_input = controller;
	m_resources = resources;

	m_sprite = resources->GetImage(Images::UNKNOWN);
	m_sprite.setTextureRect({0, 0, int(window->getSize().x), int(window->getSize().y)});

	auto && bbox = GetBBox();

	auto player = make_shared<Player>();
	{
		player->Initialize(shared_from_this());
		
		player->setScale(0.20f, 0.20f);
		player->setPosition(bbox.left + bbox.width / 2.f - player->GetBBox().width / 2.f, bbox.top + bbox.height - player->GetBBox().height);
	}

	auto snowflakeHandler = make_shared<SnowflakeHandler>();
	{
		snowflakeHandler->Initialize(shared_from_this());
		snowflakeHandler->SetMaximumSnoflakes(10);
	}
	
	m_entities.emplace_back(player);
	m_entities.emplace_back(snowflakeHandler);
}

void PlayField::ProcessInput()
{
	for (auto && entity : m_entities)
	{
		entity->ProcessInput();
	}
}

void PlayField::Update(float dt)
{
	for (auto && entity : m_entities)
	{
		entity->Update(dt);
	}
}

sf::FloatRect PlayField::GetBBox() const
{
	return getTransform().transformRect(m_sprite.getGlobalBounds());
}

sf::Vector2f PlayField::MoveToHorizontalBorder(const sf::FloatRect& playerRect) const
{
	sf::Vector2f validPos = {playerRect.left, playerRect.top};

	auto && playfieldBbox = GetBBox();

	if (playerRect.left <= playfieldBbox.left)
	{
		validPos.x = playfieldBbox.left;
	}
	else if (playerRect.left + playerRect.width >= playfieldBbox.left + playfieldBbox.width)
	{
		validPos.x = playfieldBbox.left + playfieldBbox.width - playerRect.width;
	}

	return validPos;
}

void PlayField::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(getTransform());
	target.draw(m_sprite, states);
	
	for (auto && entity : m_entities)
	{
		target.draw(*entity, states);
	}
}
