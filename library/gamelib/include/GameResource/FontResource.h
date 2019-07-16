#pragma once

#include "GameResource/BasicResource.h"

class FontResource : public BasicResource
{
public:
	FontResource();
	~FontResource() override;

	bool LoadFrom(const string& filename) override;
	bool IsLoaded() const override;
	void Unload() override;

	const sf::Font& GetFont() const;

private:
	sf::Font		m_font;
	bool			m_isLoaded {false};
};