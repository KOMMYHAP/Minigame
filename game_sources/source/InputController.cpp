#include "stdafx_game.h"
#include "InputController.h"

#include "LogMessageManager.h"

InputKey InputController::TranscodeKey(const sf::Event & event) const
{
	switch (event.key.code)
	{
	case sf::Keyboard::Space:
		return InputKey::SPACE;
	case sf::Keyboard::Left:
		return InputKey::ARROW_LEFT;
	case sf::Keyboard::Right:
		return InputKey::ARROW_RIGHT;
	case sf::Keyboard::Up:
		return InputKey::ARROW_UP;
	case sf::Keyboard::Down:
		return InputKey::ARROW_DOWN;
	case sf::Keyboard::W:
		return InputKey::W;
	case sf::Keyboard::A:
		return InputKey::A;
	case sf::Keyboard::S:
		return InputKey::S;
	case sf::Keyboard::D:
		return InputKey::D;
	case sf::Keyboard::Escape:
		return InputKey::ESC;
	case sf::Keyboard::LAlt:
		return InputKey::ALT;
	case sf::Keyboard::F4:
		return InputKey::F4;
	default:
		return InputKey::INPUT_KEY_NUMBER;
	}
}

InputKey InputController::TranscodeMouse(const sf::Event & event) const
{
	switch (event.mouseButton.button)
	{
	case sf::Mouse::Button::Left:
		return InputKey::LEFT_CLICK;
	default:
		return InputKey::INPUT_KEY_NUMBER;
	}
}

InputController::InputController()
{
	for (int i = 0, s = static_cast<int>(InputKey::INPUT_KEY_NUMBER); i < s; ++i)
	{
		auto key = static_cast<InputKey>(i);
		m_keys[key] = false;
	}
}

void InputController::ProcessInput(sf::Window & window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		InputKey key = InputKey::INPUT_KEY_NUMBER;
		bool isPressed = false;

		if (event.type == sf::Event::KeyPressed ||
			event.type == sf::Event::KeyReleased)
		{
			key = TranscodeKey(event);
			isPressed = event.type == sf::Event::KeyPressed;
		}

		if (event.type == sf::Event::MouseButtonPressed ||
			event.type == sf::Event::MouseButtonReleased)
		{
			key = TranscodeMouse(event);
			isPressed = event.type == sf::Event::MouseButtonPressed;
		}

		if (key != InputKey::INPUT_KEY_NUMBER)
		{
			m_keys[key] = isPressed;
			LOG_MESSAGE("%d key was been pressed!", static_cast<int>(key));
		}

	}
}
