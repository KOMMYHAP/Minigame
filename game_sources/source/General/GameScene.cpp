#include "stdafx_game.h"

#include "General/GameScene.h"

#include "Game.h"

shared_ptr<InputController> GameSceneCallback::GetController() const
{
	return GetGame()->GetController();
}

shared_ptr<ResourceHandler> GameSceneCallback::GetResources() const
{
	return GetGame()->GetResources();
}

shared_ptr<sf::RenderWindow> GameSceneCallback::GetRenderWindow() const
{
	return GetGame()->GetRenderWindow();
}

void GameSceneCallback::RequireScene(GameScenes::Id id) const
{
	GetGame()->SetNextScene(id);
}

void GameSceneCallback::RequireQuitGame() const
{
	GetGame()->SetNeedExit();
}
