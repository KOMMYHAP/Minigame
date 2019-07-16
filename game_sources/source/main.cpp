#include "stdafx_game.h"

#include "Application.h"

#include <Windows.h>

int WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, PSTR szCmdLine, int iCmdShow)
{
	char  szPath[MAX_PATH];
	PSTR  lpFilename;

	// Retrieve the full path for the current module.
	if ( GetModuleFileName( NULL, szPath, sizeof szPath ) == 0 )
		return -1;

	string s (szPath);

	Application app;
	int exitCode = app.Run();

	return exitCode;
}
