#include "stdafx_gamelib.h"

#include "ImageResource.h"

bool ImageResource::LoadFrom(const string& filename)
{
	m_isLoaded = m_image.loadFromFile(filename);
	return m_isLoaded;
}

void ImageResource::Unload()
{
	m_image = sf::Image();
	m_isLoaded = false;
}
