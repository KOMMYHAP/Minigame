#pragma once

#include "General/Entity.h"

class MainMenu;

class PushButton : public Entity
{
public:
	using ActionType = function<void()>;

	PushButton();

	void Initialize(shared_ptr<MainMenu> mainMenu, const sf::FloatRect & rect, const string& text);

	void ProcessInput() override;
	void Update(size_t dt) override;

	void SetOnClick(ActionType action) { m_action = std::move(action); }

	sf::FloatRect GetBBox() const;

private:
	void OnPress();
	void OnRelease(bool isInside);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Transform					m_pressingTrasform;
	bool							m_pressed {false};
	ActionType						m_action;

	sf::Sprite						m_sprite;
	sf::Text						m_text;

	weak_ptr<InputController>		m_input;
};
