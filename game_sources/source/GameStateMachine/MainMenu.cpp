#include "stdafx_game.h"

#include "GameBasic/GameObject.h"
#include "GameBasic/GameObjectManager.h"

#include "GameStateMachine/Game.h"
#include "GameStateMachine/MainMenu.h"

#include "GameResource/ResourceHandler.h"
#include "GameResource/ImageResource.h"

MainMenuScene::~MainMenuScene()
{
}

void MainMenuScene::Initialize(shared_ptr<Game> game)
{
	m_game = game;
	m_parent = game->GetRoot();
}

void MainMenuScene::Load()
{
	ResourceHandler::Instance()->Load(Resources::Type::FONT, Resources::Id::DEFAULT_FONT, "Resources/16105.ttf");
	ResourceHandler::Instance()->Load(Resources::Type::IMAGE, Resources::Id::SNOWFLAKE, "Resources/snowflake.png");
	ResourceHandler::Instance()->Load(Resources::Type::IMAGE, Resources::Id::BEER, "Resources/beer.png");
}

void MainMenuScene::Unload()
{
	ResourceHandler::Instance()->Unload(Resources::Type::FONT, Resources::Id::DEFAULT_FONT);
	ResourceHandler::Instance()->Unload(Resources::Type::IMAGE, Resources::Id::SNOWFLAKE);
	ResourceHandler::Instance()->Unload(Resources::Type::IMAGE, Resources::Id::BEER);
}

void MainMenuScene::Update(size_t dt)
{
	auto game = GetGame();
	if (!game)
	{
		return;
	}


}

void MainMenuScene::ProcessInput()
{

}

void MainMenuScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	
}
