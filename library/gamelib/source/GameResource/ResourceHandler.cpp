#include "stdafx_gamelib.h"

#include "GameResource/ResourceHandler.h"
#include "GameResource/ImageResource.h"
#include "GameResource/VideoResource.h"

#include "LogMessageManager.h"

bool ResourceHandler::Load(Resources::Type type, Resources::Id id, const string& filename)
{
	bool isSuccess = false;
	switch (type)
	{
	case Resources::Type::IMAGE:
		if (m_images.find(id) == m_images.end())
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

bool ResourceHandler::Unload(Resources::Type type, Resources::Id id)
{
	bool isSuccess = false;
	switch (type)
	{
	case Resources::Type::IMAGE:
		{
			auto it = m_images.find(id);
			isSuccess = it != m_images.end();
			m_images.erase(it);
			break;
		}
	// case Resources::Type::VIDEO:
	// 	{
	// 		auto it = m_videoes.find(id);
	// 		m_videoes.erase(it);
	// 		break;
	// 	}
	default:
		break;
	}
	
	if (!isSuccess)
	{
		LOG_WARNING("Could not unload resource [type = '%s'], [id = '%d']", Resources::ToString(type), id);
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
