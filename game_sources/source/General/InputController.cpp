#include "stdafx_game.h"

#include "General/InputController.h"
 
void InputController::ProcessInput(shared_ptr<sf::Window> window) 
{ 
	sf::Event event; 
	while (window->pollEvent(event)) 
	{ 
		if (event.type == sf::Event::Closed)
		{
			m_isWindowClosingRequired = true;
		}

		if (event.type == sf::Event::KeyPressed || 
			event.type == sf::Event::KeyReleased) 
		{ 
			bool isPressed = event.type == sf::Event::KeyPressed; 
			m_pressedKeys[event.key.code] = isPressed;
		}
 
		if (event.type == sf::Event::MouseButtonPressed || 
			event.type == sf::Event::MouseButtonReleased) 
		{ 
			bool isPressed = event.type == sf::Event::MouseButtonPressed;
			m_isLeftClick = isPressed;
		}
	} 
}

bool InputController::IsPressed(Key key) const
{
	auto it = m_pressedKeys.find(key);
	if (it != m_pressedKeys.end())
	{
		return it->second;
	}
	return false;
} 