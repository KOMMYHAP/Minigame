#pragma once

#include "BasicResource.h"

class VideoResource : public BasicResource
{
public:
	~VideoResource() override;

	bool LoadFrom(const string & filename) override;
	bool IsLoaded() const override;
	void Unload() override;

	size_t GetFramesNumber() const;
	const sf::Image & GetFrame(size_t number) const;
		
private:
	vector<sf::Image>	m_images;
	bool				m_isLoaded {false};

	class Impl;
	unique_ptr<Impl> 	m_impl;
};
