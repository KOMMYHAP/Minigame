#pragma once

#include "GameResource/BasicResource.h"

class ImageResource : public BasicResource
{
public:
	bool LoadFrom(const string& filename) override;
	bool IsLoaded() const override { return m_isLoaded; }
	void Unload() override;

	const sf::Image & GetImage() const { return m_image; }

private:
	sf::Image		m_image;
	bool			m_isLoaded {false};
};