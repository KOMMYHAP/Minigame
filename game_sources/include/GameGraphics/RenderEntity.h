#pragma once

namespace Graphics
{
	class RenderEntity : public sf::Drawable
	{
	public:
		virtual void Load() = 0;
		virtual void Unload() = 0;
		virtual bool IsReady() = 0;
	};
}