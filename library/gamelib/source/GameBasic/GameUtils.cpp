#include "stdafx_gamelib.h"
#include "GameBasic/GameUtils.h"

#include "GameBasic/GameObject.h"

void GameUtils::MoveObject(GameObject* object, sf::Vector2f point)
{
	auto local = object->GetGeometry();

	local.combine(sf::Transform(
		point.x,	0,			0, 
		0,			point.y,	0, 
		0,			0,			1)
	);

	object->SetGeometry(local);
}
