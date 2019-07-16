#pragma once

namespace Resources
{
	enum class Type
	{
		IMAGE,
		VIDEO,
		FONT,
		MUSIC,
		SOUND,

		COUNT
	};

	enum class Id
	{
		// image resources:
		BEER,
		HEART,
		BOY,
		GIRL,
		SNOWFLAKE,
		IMAGE_LAST,

		// video resources:
		CUTSCENE,
		BACKGROUND,
		VIDEO_LAST,

		// font resources:
		DEFAULT_FONT,
		FONT_LAST,
		
		// music resources:
		DEFAULT_MUSIC,
		MUSIC_LAST,
		
		// sound resources:
		SOUND_LAST,
	};

	inline const string & ToString(Type type)
	{
		static const array<string, static_cast<size_t>(Type::COUNT)> strings {
			"Image", "Video", "Font","Music", "Sound"
		};
		return strings[static_cast<size_t>(type)];
	}

}
