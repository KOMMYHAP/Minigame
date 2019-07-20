#include "stdafx_game.h"

#include "MainMenu/MainMenu.h"
#include "MainMenu/PushButton.h"
#include "LogMessageManager.h"

void MainMenu::Initialize(shared_ptr<ResourceHandler> resources, shared_ptr<InputController> input)
{
	m_resources = resources;
	m_input = input;
	
	auto start = make_shared<PushButton>();
	{
		auto buttonRect = sf::FloatRect(250, 250, 300, 100);
		start->Initialize(shared_from_this(), buttonRect, "Start Game");
		start->SetOnClick([]()
		{
			LOG_MESSAGE("Game started!");
		});	
		m_entities.push_back(start);
	}

	auto setName = make_shared<PushButton>();
	{
		auto buttonRect = sf::FloatRect(250, 350, 300, 100);
		setName->Initialize(shared_from_this(), buttonRect, "Enter Name");
		setName->SetOnClick([]()
		{
			LOG_MESSAGE("Enter you name:");
		});	
		m_entities.push_back(setName);
	}

	auto exit = make_shared<PushButton>();
	{
		auto buttonRect = sf::FloatRect(250, 450, 300, 100);
		exit->Initialize(shared_from_this(), buttonRect, "Exit");
		exit->SetOnClick([]()
		{
			LOG_MESSAGE("Game exited!");
		});	
		m_entities.push_back(exit);
	}
}

void MainMenu::ProcessInput()
{
	for (auto && entity : m_entities)
	{
		entity->ProcessInput();
	}
}

void MainMenu::Update(size_t dt)
{
	for (auto && entity : m_entities)
	{
		entity->Update(dt);
	}
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(getTransform());
	for (auto && entity : m_entities)
	{
		target.draw(*entity, states);
	}
}
