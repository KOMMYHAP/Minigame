#pragma once

#include "GameResource/BasicResource.h"

class FontResource : public BasicResource
{
public:
	bool LoadFrom(const string& filename) override;
	bool IsLoaded() const override { return m_isLoaded; }
	void Unload() override;

	const sf::Font & GetFont() const { return m_image; }
private:
	sf::Font		m_font;
	bool			m_isLoaded {false};
};