#pragma once

#include "GameResource/BasicResource.h"

class ImageResource : public BasicResource
{
public:
	ImageResource();
	~ImageResource();

	bool LoadFrom(const string& filename) override;
	bool IsLoaded() const override;
	void Unload() override;

	const sf::Image& GetImage() const;

private:
	sf::Image		m_image;
	bool			m_isLoaded {false};
};