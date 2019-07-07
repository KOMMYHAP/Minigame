#include "stdafx_game.h"

#include "SingletonManager.h"
#include "LogMessageManager.h"
#include "InputController.h"
#include "GameObjectManager.h"

int WinMain(int argc, char **argv)
{
	SingletonManager singletonSequence;
	singletonSequence.DeleteFirst(GameObjectManager::Instance());
	singletonSequence.DeleteLast(InputController::Instance());
	singletonSequence.DeleteLast(LogMessageManager::Instance());

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
