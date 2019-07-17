#include "stdafx_game.h"

#include "PlayerField.h"

#include "Player.h"

PlayerField::PlayerField()
{
}

void PlayerField::Initialize(shared_ptr<InputController> controller, shared_ptr<ResourceHandler> resources, shared_ptr<sf::Window> window)
{
	m_input = controller;
	m_resources = resources;

	m_player = make_unique<Player>();
	m_player->Initialize(shared_from_this());

	m_border.left = 0.f;
	m_border.top = 0.f;
	m_border.width = float(window->getSize().x);
	m_border.height = float(window->getSize().y) - m_border.top;
	
	m_player->setScale(0.20f, 0.20f);
	m_player->setPosition(m_border.left + m_border.width / 2.f, m_border.top + m_border.height - m_player->GetSpriteSize().height);
}

void PlayerField::ProcessInput()
{
	m_player->ProcessInput();
}

void PlayerField::Update(float dt)
{
	m_player->Update(dt);
}

bool PlayerField::IsInBorders(const sf::Vector2f& position) const
{
	return m_border.contains(position);
}

void PlayerField::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(getTransform());
	target.draw(*m_player, states);
}
