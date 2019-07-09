#pragma once

class BasicResource
{
public:
	virtual ~BasicResource() = default;
	
	virtual bool Load(const string& filename) = 0;
	virtual bool IsLoaded() const = 0;
	virtual void Unload() = 0;
	
	virtual void Draw(sf::Texture& whereToDraw, unsigned x = 0, unsigned y = 0) = 0;
};