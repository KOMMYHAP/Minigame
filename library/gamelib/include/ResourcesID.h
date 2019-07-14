#pragma once
#include <array>

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
		// ...

		IMAGE_COUNT,

		// video resources:
		// ...

		VIDEO_COUNT,
		
		// font resources:
		// ...

		FONT_COUNT,
		
		// music resources:
		// ...

		MUSIC_COUNT,
		
		// sound resources:
		// ...

		SOUND_COUNT,
	};

	constexpr const string & ToString(Type type)
	{
		constexpr std::array<string, Type::COUNT> strings {
			"Image", "Video", "Font","Music", "Sound"
		};
		return strings[static_cast<size_t>(type)];
	}

}
