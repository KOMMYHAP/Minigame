#include "stdafx_game.h"

#include "ResourceHandler.h"
#include "LogMessageManager.h" 

ResourceHandler::ResourceHandler()
{
	sf::RenderTexture defaultTexture;
	assert(defaultTexture.create(50, 50));
	defaultTexture.setRepeated(true);

	sf::RectangleShape strip({1, 150});
	strip.rotate(45);
	strip.setFillColor(sf::Color::Yellow);	

	sf::RectangleShape quadrect({50, 50});
	quadrect.setFillColor(sf::Color::Black);

	defaultTexture.draw(quadrect);
	for (float x = -50.0f; x <= 100; x += 25)
	{
		strip.setPosition(x, 0.0f);
		defaultTexture.draw(strip);
	}

	m_images[Images::UNKNOWN] = make_unique<sf::Texture>(defaultTexture.getTexture());
}

bool ResourceHandler::LoadImage(Images::Id id, const string& path)
{
	if (m_images.find(id) != m_images.end())
	{
		return true;
	}

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
		assert(false);
		auto && texturePtr = m_images.at(Images::UNKNOWN);
		sprite.setTexture(*texturePtr);
	}

	return sprite;
}
