#pragma once

class InputController : enable_shared_from_this<InputController>
{ 
public:
	void ProcessInput(shared_ptr<sf::Window> window);
	bool IsWindowClosingRequired() const { return m_isWindowClosingRequired; }
	 
	bool IsPressed(sf::Keyboard::Key key) const;
	bool IsMouseClick() const { return m_isLeftClick; }
 
private:
	using Key = sf::Keyboard::Key;

	map<Key, bool>		m_pressedKeys;
	bool				m_isLeftClick {false};

	bool				m_isWindowClosingRequired {false};
}; 