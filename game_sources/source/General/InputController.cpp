#include "stdafx_game.h"

#include "General/InputController.h"
#include "LogMessageManager.h"

void InputController::ProcessInput(shared_ptr<sf::Window> window) 
{ 
	sf::Event event;
	m_justPressedKeys.clear();
	while (window->pollEvent(event)) 
	{ 
		if (event.type == sf::Event::Closed)
		{
			m_isWindowClosingRequired = true;
		}

		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
		{
			bool isPressed = event.type == sf::Event::KeyPressed;
			m_justPressedKeys[event.key.code] = isPressed;
			m_pressedDownKeys[event.key.code] = isPressed;
		}

		if (event.type == sf::Event::MouseButtonPressed || 
			event.type == sf::Event::MouseButtonReleased) 
		{ 
			bool isPressed = event.type == sf::Event::MouseButtonPressed;
			m_isMousePressed = isPressed;
			m_mousePos = { event.mouseButton.x, event.mouseButton.y};
		}
	} 
}

bool InputController::IsJustPressed(Key key) const
{
	auto it = m_justPressedKeys.find(key);
	if (it != m_justPressedKeys.end())
	{
		return it->second;
	}
	return false;
}

bool InputController::IsKeyDown(sf::Keyboard::Key key) const
{
	auto it = m_pressedDownKeys.find(key);
	if (it != m_pressedDownKeys.end())
	{
		return it->second;
	}
	return false;
}
