#pragma once

#include "BasicResource.h"

class VideoResource : BasicResource
{
public:
	~VideoResource() override;

	bool Load(const string & filename) override;
	bool IsLoaded() const override;
	void Unload() override;
	
	void Draw(sf::Texture & whereToDraw, unsigned int x = 0, unsigned int y = 0);
	
	//void StopPlay();
	//void PausePlay();
	//void SetLooped(bool value);
	
private:
	class Impl;
	unique_ptr<Impl> 	m_impl;
	
	bool				m_isLoaded {false};
};
