#pragma once

#include "GameResource/ResourcesID.h"
#include "Singleton.h"

class BasicResource;

class ImageResource;
class VideoResource;
class FontResource;
// class MusicResource;
// class SoundResource;

class ResourceHandler : public Singleton<ResourceHandler>
{
public:
	ResourceHandler();
	~ResourceHandler() override;

	bool Load(Resources::Type type, Resources::Id id, const string & filename);
	bool Unload(Resources::Type type, Resources::Id id);
	
	ImageResource * GetImage(Resources::Id id) const;
	VideoResource * GetVideo(Resources::Id id) const;
	FontResource *	GetFont(Resources::Id id) const;
	// MusicResource *	GetMusic(Resources::Id id) const;
	// SoundResource *	GetSound(Resources::Id id) const;

private:
	map<Resources::Id, unique_ptr<ImageResource>>		m_images;
	map<Resources::Id, unique_ptr<VideoResource>>		m_videoes;
	map<Resources::Id, unique_ptr<FontResource>>		m_fonts;
	// map<Resources::Id, unique_ptr<BasicResource>>		m_music;
	// map<Resources::Id, unique_ptr<BasicResource>>		m_sound;
};
