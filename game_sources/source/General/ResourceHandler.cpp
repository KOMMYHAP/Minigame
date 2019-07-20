#include "stdafx_game.h"

#include "General/ResourceHandler.h"

#include "LogMessageManager.h" 

ResourceHandler::ResourceHandler()
{
	m_textures[Textures::DEFAULT] = make_unique<sf::Texture>(CreateDefaultTexture());
}

bool ResourceHandler::LoadTexture(Textures::Id id, const string& path)
{
	if (m_textures.find(id) != m_textures.end())
	{
		return true;
	}

	auto texture = make_unique<sf::Texture>();
	bool success = texture->loadFromFile(path);
	if (success)
	{
		texture->setRepeated(true);
		texture->setSmooth(true);
		m_textures[id] = move(texture);	
	}

	return success;
}

const sf::Texture* ResourceHandler::GetTexture(Textures::Id id) const
{
	auto it = m_textures.find(id);
	if (it != m_textures.end())
	{
		return it->second.get();
	}
	return nullptr;
}

const sf::Texture* ResourceHandler::GetDefaultTexture() const
{
	return GetTexture(Textures::DEFAULT);
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

const sf::Texture* ResourceHandler::GetImage(Images::Id id) const
{
	auto it = m_images.find(id);
	if (it != m_images.end())
	{
		return it->second.get();
	}
	return nullptr;
}

bool ResourceHandler::LoadFont(Fonts::Id id, const string & path)
{
	if (m_fonts.find(id) != m_fonts.end())
	{
		return true;
	}

	auto font = make_unique<sf::Font>();
	bool success = font->loadFromFile(path);
	if (success)
	{
		m_fonts[id] = move(font);
	}

	return success;
}

const sf::Font* ResourceHandler::GetFont(Fonts::Id id) const 
{
	auto it = m_fonts.find(id);
	if (it != m_fonts.end())
	{
		return it->second.get();
	}
	LOG_ERROR("ResourceHandler could not find font %1%!", id);
	return nullptr;
}

bool ResourceHandler::LoadMusic(Music::Id id, const string & path) 
{
	if (m_music.find(id) != m_music.end())
	{
		return true;
	}

	auto music = make_unique<sf::Music>();
	bool success = music->openFromFile(path);
	if (success)
	{
		m_music[id] = move(music);
	}

	return success;
}

sf::Music* ResourceHandler::GetMusic(Music::Id id) const
{
	auto it = m_music.find(id);
	if (it != m_music.end())
	{
		return it->second.get();
	}
	LOG_ERROR("ResourceHandler could not find music %1%!", id);
	return nullptr;
}

sf::Texture ResourceHandler::CreateDefaultTexture()
{
	sf::RenderTexture defaultTexture;
	assert(defaultTexture.create(50, 50));
	defaultTexture.setRepeated(true);
	defaultTexture.setSmooth(true);

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

	return defaultTexture.getTexture();
}
