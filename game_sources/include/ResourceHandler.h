#pragma once

namespace Images
{
	enum Id
	{
		UNKNOWN,
		GIRL,
		SNOWFLAKE,
		COUNT	
	};
}

namespace Fonts
{
	enum Id
	{
		DEFAULT,
		COUNT
	};
}

class ResourceHandler : enable_shared_from_this<ResourceHandler>
{
public:
	ResourceHandler();

	bool LoadImage(Images::Id id, const string & path);
	sf::Sprite GetImage(Images::Id id) const;

private:
	map<Images::Id, unique_ptr<sf::Texture>>	m_images;
};