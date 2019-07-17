#include "stdafx_game.h"

#include "ResourceHandler.h"
#include "LogMessageManager.h" 

ResourceHandler::ResourceHandler()
{
	sf::RenderTexture defaultTexture;

	sf::RectangleShape strip({100, 5});
	strip.rotate(-45);
	strip.setFillColor(sf::Color::Yellow);	

	defaultTexture.create(100, 100);
	defaultTexture.setRepeated(true);

	sf::RectangleShape quadrect({100, 100});
	quadrect.setFillColor(sf::Color::Black);

	defaultTexture.draw(quadrect);

	for (int i = 0; i < 10; ++i)
	{
		strip.setPosition(10.f * i, 0);
		defaultTexture.draw(strip);
	}

	m_images[Images::UNKNOWN] = make_unique<sf::Texture>(defaultTexture.getTexture());
}

bool ResourceHandler::LoadImage(Images::Id id, const string& path)
{
	assert(m_images.find(id) == m_images.end());

	auto image = make_unique<sf::Texture>();
	bool success = image->loadFromFile(path);
	if (success)
	{
		m_images[id] = move(image);	
	}

	return success;
}

sf::Sprite ResourceHandler::GetImage(Images::Id id) const
{
	sf::Sprite sprite;

	auto it = m_images.find(id);
	if (it != m_images.end())
	{
		auto && texturePtr = it->second;
		sprite.setTexture(*texturePtr);
	}
	else
	{
		auto && texturePtr = m_images.at(Images::UNKNOWN);
		sprite.setTexture(*texturePtr);
	}

	return sprite;
}
