#pragma once

#include "General/Entity.h"
#include "General/ResourceHandler.h"

class MainMenu;

class PushButton : public Entity
{
public:
	using ActionType = function<void()>;

	PushButton();

	void Initialize(shared_ptr<MainMenu> mainMenu, const sf::FloatRect & rect);
	
	void SetTexture(const sf::Texture * texture);
	void SetImage(const sf::Texture * texture);
	void SetText(const string & text, size_t size = 36, sf::Color fillColor = sf::Color::White, sf::Color outlineColor = sf::Color::Black);

	void ProcessInput() override;
	void Update(float dt) override;

	void SetOnClick(ActionType action) { m_action = std::move(action); }

	sf::FloatRect GetBBox() const;

private:
	void OnPress();
	void OnRelease(bool isInside);

	void UpdateTextGeometry();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Transform					m_pressingTrasform;
	bool							m_pressed {false};
	ActionType						m_action;

	sf::FloatRect					m_buttonRect;
	sf::Sprite						m_sprite;

	bool							m_fontLoaded {false};
	sf::Text						m_text;

	weak_ptr<MainMenu>				m_mainMenu;
};
