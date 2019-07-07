#pragma once

#include "SingletonManager.h"

class Application
{
public:
	Application(int argc, char ** argv);

	int Run();

private:
	void SingletonSequenceInitialize();

	bool IsTryToShutdown() const;

	SingletonManager		m_singletonSequence;
};
