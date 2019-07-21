#pragma once

#include "General/VideoSource.h"

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
		BOY,
		SNOWFLAKE,
		HEART,
		BEER,
		BUTTON_START,
		BUTTON_EXIT,
		BACKGROUND,
		COUNT	
	};
}

namespace Fonts
{
	enum Id
	{
		DEFAULT,
		ICE_CAPS,
		CUTSCENE,
		TIMES_NEW_ROMAN,
		COUNT
	};
}

namespace Musics
{
	enum Id
	{
		PLAYFIELD,
		COUNT
	};
}

namespace Videoes
{
	enum Id
	{
		PLAYFIELD_BACKGROUND,
		CUTSCENE,
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
	
	bool LoadMusic(Musics::Id id, const string & path);
	sf::Music* GetMusic(Musics::Id id) const;

	bool LoadVideo(Videoes::Id id, const string &path);
	const VideoSource * GetVideo(Videoes::Id id) const;

private:
	sf::Texture CreateDefaultTexture();

	map<Textures::Id, unique_ptr<sf::Texture>>	m_textures;
	map<Images::Id, unique_ptr<sf::Texture>>	m_images;
	map<Fonts::Id, unique_ptr<sf::Font>>		m_fonts;
	map<Musics::Id, unique_ptr<sf::Music>>		m_music;
	map<Videoes::Id, unique_ptr<VideoSource>>	m_videoes;
};