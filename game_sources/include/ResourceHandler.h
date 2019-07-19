#pragma once

namespace Images
{
	enum Id
	{
		UNKNOWN,
		GIRL,
		SNOWFLAKE,
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

class ResourceHandler : enable_shared_from_this<ResourceHandler>
{
public:
	ResourceHandler();

	bool LoadImage(Images::Id id, const string & path);
	const sf::Texture * GetTexture(Images::Id id) const;
	
	bool LoadFont(Fonts::Id id, const string & path);
	const sf::Font * GetFont(Fonts::Id id) const;
	
	bool LoadMusic(Music::Id id, const string & path);
	sf::Music* GetMusic(Music::Id id) const;

private:
	sf::Texture CreateDefaultTexture();

	map<Images::Id, unique_ptr<sf::Texture>>	m_images;
	map<Fonts::Id, unique_ptr<sf::Font>>		m_fonts;
	map<Music::Id, unique_ptr<sf::Music>>		m_music;
};