#pragma once
#include "Singleton.h"

enum class InputKey
{
	W, A, S, D,
	ARROW_LEFT, ARROW_RIGHT, ARROW_UP, ARROW_DOWN,
	SPACE,
	LEFT_CLICK,
	ESC,
	INPUT_KEY_NUMBER
};

class InputController : public Singleton<InputController>
{
public:
	InputController();

	void ProcessInput(sf::Window & window);
	
	bool IsPressed(InputKey key) const { return m_keys.at(key); }
	bool IsReleased(InputKey key) const { return !IsPressed(key); }

	bool IsTryToShutdown() const { return m_isTryToShutdown; }

private:
	InputKey TranscodeKey(const sf::Event & event) const;
	InputKey TranscodeMouse(const sf::Event & event) const;

	map<InputKey, bool>		m_keys;
	bool					m_isTryToShutdown {false};
};
