#pragma once

class InputController
{ 
public:
	void ProcessInput(shared_ptr<sf::Window> window);
	bool IsWindowClosingRequired() const { return m_isWindowClosingRequired; }
	 
	bool IsJustPressed(sf::Keyboard::Key key) const;
	bool IsKeyDown(sf::Keyboard::Key key) const;
	bool IsMousePressed() const { return m_isMousePressed; }

	sf::Vector2i GetMousePosition() const { return m_mousePos; }
 
private:
	using Key = sf::Keyboard::Key;
	
	map<Key, bool>		m_justPressedKeys;
	map<Key, bool>		m_pressedDownKeys;

	bool				m_isMousePressed			{false};
	sf::Vector2i		m_mousePos;

	bool				m_isWindowClosingRequired	{false};
}; 