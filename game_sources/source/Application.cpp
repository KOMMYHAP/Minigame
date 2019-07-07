#include "stdafx_game.h"
#include "Application.h"

#include "InputController.h"

Application::Application(int argc, char** argv)
{
	// parsing command line arguments
}

int Application::Run()
{
	auto fullscreenVideoModes = sf::VideoMode::getFullscreenModes();

	sf::Window window(fullscreenVideoModes[0], "Snowfall", sf::Style::Fullscreen | sf::Style::Close);
	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		InputController::Instance()->ProcessInput(window);

		if (InputController::Instance()->IsPressed(InputKey::ESC) ||
			InputController::Instance()->IsPressed(InputKey::ALT) && 
			InputController::Instance()->IsPressed(InputKey::F4))
		{
			break;
		}

		window.display();
	}

	return 0;
}
