#include "stdafx_game.h"
#include "Application.h"

#include "InputController.h"

Application::Application(int argc, char** argv)
{
	// parse command line arguments
}

int Application::Run()
{
	// auto fullscreenModes = sf::VideoMode::getFullscreenModes();
	auto videoMode = sf::VideoMode(800, 600);

	sf::Window window(videoMode, "Snowfall");
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		InputController::Instance()->ProcessInput(window);

		if (IsTryToShutdown())
		{
			// break down main loop or 
			// forward a signal into the Game to prevent user
			break;
		}

		window.display();
	}

	return 0;
}

bool Application::IsTryToShutdown() const
{
	return InputController::Instance()->IsTryToShutdown() ||
		InputController::Instance()->IsPressed(InputKey::ESC);
}
