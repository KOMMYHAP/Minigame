#include "stdafx_gamelib.h"

#include "GameResource/ImageResource.h"

ImageResource::ImageResource()
{
}

ImageResource::~ImageResource()
{
}

bool ImageResource::LoadFrom(const string& filename)
{
	m_isLoaded = m_image.loadFromFile(filename);
	return m_isLoaded;
}

bool ImageResource::IsLoaded() const
{
	return m_isLoaded;
}

const sf::Image& ImageResource::GetImage() const
{
	return m_image;
}

void ImageResource::Unload()
{
	m_image = sf::Image();
	m_isLoaded = false;
}
