#include "stdafx_game.h"

#include "General/InputController.h"
#include "General/ResourceHandler.h"

#include "GameField/PlayField.h"
#include "MainMenu/MainMenu.h"

int main(int argc, char **argv)
{
	auto window = make_shared<sf::RenderWindow>();
	window->create(sf::VideoMode(800, 600), "Snowflake", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(60);
	
	auto inputController = make_shared<InputController>();
	auto resourceHandler = make_shared<ResourceHandler>();

	// auto playField = make_shared<PlayField>();
	// playField->Initialize(inputController, resourceHandler, window);

	auto mainMenu = make_shared<MainMenu>();
	mainMenu->Initialize(resourceHandler, inputController);

	shared_ptr<Entity> scene = mainMenu;

	sf::Clock clock;
	const auto timePerFrame = static_cast<int>(std::ceil(1000.0f / 60.0f));
    while (window->isOpen())
    {
        inputController->ProcessInput(window);

		if (inputController->IsWindowClosingRequired())
		{
			window->close();
			break;
		}

		scene->ProcessInput();

		int dt = clock.getElapsedTime().asMilliseconds();

		do
		{
			scene->Update(dt);
			dt -= timePerFrame;
		} while (dt >= timePerFrame);

        window->clear();
        window->draw(*scene);
        window->display();

		clock.restart();
    }

    return 0;
}
