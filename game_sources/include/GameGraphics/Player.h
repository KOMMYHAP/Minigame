#pragma once

#include "GameGraphics/RenderEntity.h"

class GameObject;
class ImageResource;

namespace Graphics
{
	class Player : public RenderEntity
	{
	public:
		void Initialize(GameObject * object);

		void Load() override;
		void Unload() override;
		bool IsReady() override { return m_isLoaded; }

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		sf::Texture				m_texture;
		GameObject *			m_object	{nullptr};
		bool					m_isLoaded	{false};
	};
}
