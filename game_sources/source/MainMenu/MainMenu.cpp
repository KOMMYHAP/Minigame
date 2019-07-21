#include "stdafx_game.h"

#include "MainMenu/MainMenu.h"
#include "MainMenu/PushButton.h"
#include "General/GameScene.h"
#include "LogMessageManager.h"

void MainMenu::Initialize(shared_ptr<GameSceneCallback> callback)
{
	m_callback = callback;
}

void MainMenu::OnStartScene()
{
	LOG_MESSAGE("Scene [MainMenu] started.");

	if (m_isLoaded)
	{
		return;
	}

	auto success = GetResources()->LoadFont(Fonts::ICE_CAPS, "Resources/IceCaps.ttf");
	assert(success);
	{
		if (auto ptr = GetResources()->GetFont(Fonts::ICE_CAPS))
		{
			m_text.setFont(*ptr);
			m_text.setCharacterSize(175);
			m_text.setFillColor(sf::Color(99, 180, 255));
			m_text.setOutlineColor(sf::Color::White);
			m_text.setOutlineThickness(10.f);
			m_text.setLetterSpacing(1.2f);
			m_text.setString("Snowfall");

			auto textBbox = m_text.getGlobalBounds();
			auto window = m_callback->GetRenderWindow();

			textBbox.width = std::min(textBbox.width, float(window->getSize().x));

			sf::Vector2f offset = {
				(window->getSize().x - textBbox.width - textBbox.left) / 2.0f,
				-10
			};
			m_text.move(offset);
		}
	}

	auto start = make_shared<PushButton>();
	{
		auto buttonRect = sf::FloatRect(350, 350, 300, 100);
		start->Initialize(shared_from_this(), buttonRect);

		bool success = GetResources()->LoadImage(Images::BUTTON_START, "Resources/start.png");
		assert(success);
		if (auto ptr = GetResources()->GetImage(Images::BUTTON_START))
		{
			start->SetImage(ptr);
		}

		start->SetOnClick([this]()
		{
			LOG_MESSAGE("Game started!");
			m_callback->RequireScene(GameScenes::PLAYFIELD);
		});	
		m_entities.push_back(start);
	}

	auto exit = make_shared<PushButton>();
	{
		auto buttonRect = sf::FloatRect(350, 450, 300, 100);
		exit->Initialize(shared_from_this(), buttonRect);

		bool success = GetResources()->LoadImage(Images::BUTTON_EXIT, "Resources/exit.png");
		assert(success);
		if (auto ptr = GetResources()->GetImage(Images::BUTTON_EXIT))
		{
			exit->SetImage(ptr);
		}

		exit->SetOnClick([this]()
		{
			LOG_MESSAGE("Game exited!");
			m_callback->RequireQuitGame();
		});	
		m_entities.push_back(exit);
	}

	m_isLoaded = true;
}

void MainMenu::OnEndScene()
{
	LOG_MESSAGE("Scene [MainMenu] completed.");
}

void MainMenu::ProcessInput()
{
	for (auto && entity : m_entities)
	{
		entity->ProcessInput();
	}
}

void MainMenu::Update(float dt)
{
	for (auto && entity : m_entities)
	{
		entity->Update(dt);
	}
}

void MainMenu::Draw(sf::RenderWindow& window)
{
	sf::RenderStates states;
	window.draw(m_text);
	for (auto && entity : m_entities)
	{
		window.draw(*entity, states);
	}
}