#include "stdafx_game.h"

#include "SingletonManager.h"
#include "LogMessageManager.h"
#include "InputController.h"
#include "GameObjectManager.h"

#include "Application.h"

int WinMain(int argc, char **argv)
{
	SingletonManager singletonSequence;

	singletonSequence.DeleteFirst(GameObjectManager::Instance());
	singletonSequence.DeleteLast(InputController::Instance());
	singletonSequence.DeleteLast(LogMessageManager::Instance());

	Application app(argc, argv);
	int exitCode = app.Run();

	return exitCode;
}
