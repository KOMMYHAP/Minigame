#pragma once

class Application
{
public:
	Application(int argc, char ** argv);

	int Run();

private:
	bool IsTryToShutdown() const;
};