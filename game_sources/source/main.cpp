#include "stdafx_game.h"
#include "InputController.h"
#include "ResourceHandler.h"

#include "PlayField.h"

int main(int argc, char **argv)
{
	auto inputController = make_shared<InputController>();
	auto resourceHandler = make_shared<ResourceHandler>();
	
	auto window = make_shared<sf::RenderWindow>();
	window->create(sf::VideoMode(800, 600), "Snowflake", sf::Style::Titlebar | sf::Style::Close);
	window->setFramerateLimit(60);

	auto playField = make_shared<PlayField>();
	playField->Initialize(inputController, resourceHandler, window);

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

		playField->ProcessInput();

		int dt = clock.getElapsedTime().asMilliseconds();

		do
		{
			playField->Update(dt);
			dt -= timePerFrame;
		} while (dt >= timePerFrame);

        window->clear();
        window->draw(*playField);
        window->display();

		clock.restart();
    }

    return 0;
}
