#pragma once

namespace Textures
{
	enum Id
	{
		DEFAULT,
		BUTTON,
		PANEL,
		COUNT
	};
}

namespace Images
{
	enum Id
	{
		GIRL,
		SNOWFLAKE,
		HEART,
		BEER,
		COUNT	
	};
}

namespace Fonts
{
	enum Id
	{
		DEFAULT,
		COUNT
	};
}

namespace Music
{
	enum Id
	{
		PLAYFIELD,
		COUNT
	};
}

class ResourceHandler
{
public:
	ResourceHandler();
	
	bool LoadTexture(Textures::Id id, const string & path);
	const sf::Texture* GetTexture(Textures::Id id) const;
	const sf::Texture* GetDefaultTexture() const;
	
	bool LoadImage(Images::Id id, const string & path);
	const sf::Texture* GetImage(Images::Id id) const;
	
	bool LoadFont(Fonts::Id id, const string & path);
	const sf::Font* GetFont(Fonts::Id id) const;
	
	bool LoadMusic(Music::Id id, const string & path);
	sf::Music* GetMusic(Music::Id id) const;

private:
	sf::Texture CreateDefaultTexture();

	map<Textures::Id, unique_ptr<sf::Texture>>	m_textures;
	map<Images::Id, unique_ptr<sf::Texture>>	m_images;
	map<Fonts::Id, unique_ptr<sf::Font>>		m_fonts;
	map<Music::Id, unique_ptr<sf::Music>>		m_music;
};