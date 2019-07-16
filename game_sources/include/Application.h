#pragma once

#include "SingletonManager.h"

class Game;

class Application : public enable_shared_from_this<Application>
{
public:
	Application();
	~Application();

	int Run();

	const sf::VideoMode & GetCurrentVideoMode() const { return m_videoMode; }
	sf::RenderWindow & GetRenderWindow() { return m_window; }

private:
	void SingletonSequenceInitialize();
	
	sf::VideoMode			m_videoMode;
	sf::RenderWindow		m_window;

	SingletonManager		m_singletonSequence;

	shared_ptr<Game>		m_game;
};
