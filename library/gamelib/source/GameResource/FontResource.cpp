#include "stdafx_gamelib.h"

#include "GameResource/FontResource.h"

bool FontResource::LoadFrom(const string& filename)
{
	m_isLoaded = m_font.loadFromFile(filename);
	return m_isLoaded;
}

void FontResource::Unload()
{
	m_font = sf::Font();
	m_isLoaded = false;
}
