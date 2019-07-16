#include "stdafx_gamelib.h"

#include "GameResource/VideoResource.h"

VideoResource::VideoResource()
{

}

VideoResource::~VideoResource()
{

}

bool VideoResource::LoadFrom(const string& filename)
{
	return false;
}

bool VideoResource::IsLoaded() const
{
	return false;
}

void VideoResource::Unload()
{
}

size_t VideoResource::GetFramesNumber() const
{
	return 0;
}

const sf::Image& VideoResource::GetFrame(size_t number) const
{
	static sf::Image i;
	return i;
}

class VideoResource::Impl {};
