#pragma once

#include "BasicResource.h"

class ImageResource : public BasicResource
{
public:
	bool Load(const string& filename) override;
	void Unload() override;

	bool IsLoaded() const override { return m_isLoaded; }

	void Draw(sf::Texture& whereToDraw, unsigned x = 0, unsigned y = 0) override;

private:
	sf::Texture		m_texture;
	bool			m_isLoaded {false};
};