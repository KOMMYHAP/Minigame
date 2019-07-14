#include "stdafx_gamelib.h"

#include "ResourceHandler.h"

#include "ImageResource.h"
#include "VideoResource.h"
#include "LogMessageManager.h"

bool ResourceHandler::Load(Resources::Type type, Resources::Id id, const string& filename)
{
	bool isSuccess = false;
	switch (type)
	{
	case Resources::Type::IMAGE:
		{
			auto res = make_unique<ImageResource>();
			isSuccess = res->LoadFrom(filename);
			m_images[id] = move(res);	
			break;
		}
	case Resources::Type::VIDEO:
		{
			// auto res = make_unique<VideoResource>();
			// isSuccess = res->LoadFrom(filename);
			// m_videoes[id] = move(res);	
			break;
		}
	default:
		return false;
	}

	if (!isSuccess)
	{
		LOG_WARNING("Could not load resource [type = '%s'], [id = '%d'], [filename = '%s']", Resources::ToString(type), id, filename);
	}

	return isSuccess;
}

ImageResource* ResourceHandler::GetImage(Resources::Id id) const
{
	auto it = m_images.find(id);
	if (it != m_images.end())
	{
		return it->second.get();
	}
	return nullptr;
}

VideoResource* ResourceHandler::GetVideo(Resources::Id id) const
{
	auto it = m_videoes.find(id);
	if (it != m_videoes.end())
	{
		return it->second.get();
	}
	return nullptr;
}
