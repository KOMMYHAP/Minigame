#include "stdafx_game.h"

#include "GameGraphics/Player.h"

#include "GameBasic/GameObject.h"
#include "GameResource/ImageResource.h"
#include "GameResource/ResourceHandler.h"

namespace Graphics
{
	void Player::Initialize(GameObject* object)
	{
		m_object = object;
	}

	void Player::Load()
	{
		ResourceHandler::Instance()->Load(Resources::Type::IMAGE, Resources::Id::GIRL, "Resources/girl.png");
		if (auto res = ResourceHandler::Instance()->GetImage(Resources::Id::GIRL))
		{
			m_texture.loadFromImage(res->GetImage());
			m_isLoaded = true;
		}
	}

	void Player::Unload()
	{
		ResourceHandler::Instance()->Unload(Resources::Type::IMAGE, Resources::Id::GIRL);
		m_texture = sf::Texture();
	}

	void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform.combine(m_object->GetGeometry());
		sf::Sprite sprite(m_texture);
		target.draw(sprite, states);
	}
}
