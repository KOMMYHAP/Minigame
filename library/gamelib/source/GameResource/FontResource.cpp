#include "stdafx_gamelib.h"

#include "GameResource/FontResource.h"

FontResource::FontResource()
{
}

FontResource::~FontResource()
{
}

bool FontResource::LoadFrom(const string& filename)
{
	m_isLoaded = m_font.loadFromFile(filename);
	return m_isLoaded;
}

bool FontResource::IsLoaded() const
{
	return m_isLoaded;
}

const sf::Font& FontResource::GetFont() const
{
	return m_font;
}

void FontResource::Unload()
{
	m_font = sf::Font();
	m_isLoaded = false;
}
