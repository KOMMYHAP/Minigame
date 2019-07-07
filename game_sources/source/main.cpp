#include "stdafx_game.h"

#include "Application.h"

int WinMain(int argc, char **argv)
{
	Application app(argc, argv);
	int exitCode = app.Run();

	return exitCode;
}
