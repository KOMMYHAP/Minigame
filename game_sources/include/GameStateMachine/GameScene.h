#pragma once

#include "Entities/Entity.h"
#include "GameGraphics/RenderEntity.h"

class Game;

class GameScene : public Entities::Entity, public Graphics::RenderEntity
{
public:
	virtual ~GameScene() = default;

	virtual void Initialize(shared_ptr<Game> game) = 0;
};