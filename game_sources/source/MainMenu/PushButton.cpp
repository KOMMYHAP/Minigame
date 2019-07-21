#include "stdafx_game.h"

#include "MainMenu/PushButton.h"
#include "MainMenu/MainMenu.h"

#include "General/ResourceHandler.h"
#include "General/InputController.h"

PushButton::PushButton()
{

}

void PushButton::Initialize(shared_ptr<MainMenu> mainMenu, const sf::FloatRect & rect)
{
	m_mainMenu = mainMenu;
	m_buttonRect = rect;

	auto resources = mainMenu->GetResources();
	if (auto defaultTexture = resources->GetDefaultTexture())
	{
		SetTexture(defaultTexture);
	}

	move(rect.left, rect.top);
}

void PushButton::SetTexture(const sf::Texture* texture)
{
	m_sprite.setTexture(*texture);
	sf::IntRect textureRect = {0, 0, int(m_buttonRect.width), int(m_buttonRect.height)};
	m_sprite.setTextureRect(textureRect);
}

void PushButton::SetImage(const sf::Texture* texture)
{
	m_sprite.setTexture(*texture, true);
	auto size = texture->getSize();
	m_sprite.setScale(m_buttonRect.width / size.x, m_buttonRect.height / size.y);
}

void PushButton::SetText(const string& text, size_t size, sf::Color fillColor, sf::Color outlineColor)
{
	if (!m_fontLoaded)
	{
		auto resources = m_mainMenu.lock()->GetResources();

		resources->LoadFont(Fonts::DEFAULT, "Resources/16105.ttf");
		if (auto ptr = resources->GetFont(Fonts::DEFAULT))
		{
			m_text.setFont(*ptr);
			m_text.setCharacterSize(size);
			m_text.setFillColor(fillColor);
			m_text.setOutlineColor(outlineColor);
		}
		m_fontLoaded = true;
	}

	m_text.setString(text);
	UpdateTextGeometry();
}

void PushButton::ProcessInput()
{
	auto input = m_mainMenu.lock()->GetController();
	auto pos = input->GetMousePosition();
	auto bbox = GetBBox();
	bool isInside = bbox.contains(float(pos.x), float(pos.y));

	if (input->IsMousePressed())
	{
		if (!m_pressed && isInside)
		{
			OnPress();
		}
	}
	else
	{
		if (m_pressed)
		{
			OnRelease(isInside);
		}
	}
}

void PushButton::Update(float dt)
{
}

sf::FloatRect PushButton::GetBBox() const
{
	return getTransform().transformRect(m_sprite.getGlobalBounds());
}

void PushButton::OnPress()
{
	auto bbox = GetBBox();

	m_pressingTrasform = sf::Transform::Identity;
	m_pressingTrasform.scale(0.85f, 0.85f);
	auto compressed = m_pressingTrasform.transformRect(bbox);
	sf::Vector2f offsetToCenter = {
		(bbox.width - compressed.width) / 2.0f, 
		(bbox.height - compressed.height) / 2.0f
	};
	m_pressingTrasform.translate(offsetToCenter);

	m_pressed = true;
}

void PushButton::OnRelease(bool isInside)
{
	m_pressed = false;

	if (!isInside)
	{
		return;
	}

	setScale(1.0f, 1.0f);
	if (m_action)
	{
		m_action();
	}
}

void PushButton::UpdateTextGeometry()
{
	auto textBbox = m_text.getGlobalBounds();
	auto spriteBbox = m_sprite.getGlobalBounds();

	textBbox.width = std::min(textBbox.width, spriteBbox.width);
	textBbox.height = std::min(textBbox.height, spriteBbox.height);

	sf::Vector2f offset = {
		(spriteBbox.width - textBbox.width - textBbox.left) / 2.0f,
		(spriteBbox.height - textBbox.height) / 2.0f - textBbox.top
	};
	m_text.move(offset);
}

void PushButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	auto combined = getTransform() * (m_pressed ? m_pressingTrasform : sf::Transform::Identity);
	states.transform.combine(combined);
	target.draw(m_sprite, states);
	states.transform.combine(m_sprite.getTransform());
	target.draw(m_text, states);
}
