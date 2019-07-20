#include "stdafx_game.h"

#include "MainMenu/PushButton.h"
#include "MainMenu/MainMenu.h"

#include "General/ResourceHandler.h"
#include "General/InputController.h"

PushButton::PushButton()
{

}

void PushButton::Initialize(shared_ptr<MainMenu> mainMenu, const sf::FloatRect & rect, const string & text)
{
	m_input = mainMenu->GetController();

	auto resources = mainMenu->GetResources();

	resources->LoadTexture(Textures::BUTTON, "Resources/button.png");
	if (auto ptr = resources->GetTexture(Textures::BUTTON))
	{
		m_sprite.setTexture(*ptr);
	}
	else if (auto defaultTexture = resources->GetDefaultTexture())
	{
		m_sprite.setTexture(*defaultTexture);
	}

	sf::IntRect textureRect = {0, 0, int(rect.width), int(rect.height)};
	m_sprite.setTextureRect(textureRect);

	resources->LoadFont(Fonts::DEFAULT, "Resources/16105.ttf");
	if (auto ptr = resources->GetFont(Fonts::DEFAULT))
	{
		m_text.setFont(*ptr);
		m_text.setCharacterSize(36);
		m_text.setFillColor(sf::Color::White);
		m_text.setOutlineColor(sf::Color::Black);
		m_text.setString(text);

		auto textBbox = m_text.getGlobalBounds();
		textBbox.width = std::min(textBbox.width, rect.width);
		textBbox.height = std::min(textBbox.height, rect.height);
		
		auto spriteBbox = m_sprite.getGlobalBounds();
		sf::Vector2f offset = {
			(spriteBbox.width - textBbox.width - textBbox.left) / 2.0f,
			(spriteBbox.height - textBbox.height) / 2.0f - textBbox.top
		};
		m_text.move(offset);
	}

	move(rect.left, rect.top);
}

void PushButton::ProcessInput()
{
	auto input = m_input.lock();
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

void PushButton::Update(size_t dt)
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

void PushButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	auto combined = getTransform() * (m_pressed ? m_pressingTrasform : sf::Transform::Identity);
	states.transform.combine(combined);
	target.draw(m_sprite, states);
	target.draw(m_text, states);

}
