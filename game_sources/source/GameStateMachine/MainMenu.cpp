#include "stdafx_game.h"

#include "GameBasic/GameObject.h"
#include "GameBasic/GameObjectManager.h"

#include "GameStateMachine/Game.h"
#include "GameStateMachine/MainMenu.h"

#include "Entities/Player.h"
#include "GameGraphics/Player.h"

MainMenuScene::MainMenuScene()
{
	m_object = GameObjectManager::Instance()->Create("mainMenuScene", nullptr);
}

MainMenuScene::~MainMenuScene()
{
	if (!m_object->GetParent())
	{
		GameObjectManager::Instance()->Delete(m_object);
	}
}

void MainMenuScene::Initialize(shared_ptr<Game> game)
{
	m_game = game;
	m_object->SetParent(game->GetRoot());

	auto player = make_unique<Entities::Player>();
	auto gPlayer = make_unique<Graphics::Player>();

	player->Initialize(m_object->GetParentToChange());
	gPlayer->Initialize(player->GetGameObject());

	m_entities.emplace_back(move(player));
	m_graphicsEntities.emplace_back(move(gPlayer));

}

void MainMenuScene::Load()
{
	for (auto && entity : m_graphicsEntities)
	{
		entity->Load();
	}
}

void MainMenuScene::Unload()
{
	for (auto && entity : m_graphicsEntities)
	{
		entity->Unload();
	}
}

void MainMenuScene::Update(size_t dt)
{
	auto game = GetGame();
	if (!game)
	{
		return;
	}

	for (auto && entity : m_entities)
	{
		entity->Update(dt);
	}
}

void MainMenuScene::ProcessInput()
{
	for (auto && entity : m_entities)
	{
		entity->ProcessInput();
	}
}

bool MainMenuScene::IsReady()
{
	for (auto && entity : m_graphicsEntities)
	{
		if (!entity->IsReady())
		{
			return false;
		}
	}
	return true;
}

void MainMenuScene::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto && entity : m_graphicsEntities)
	{
		target.draw(*entity, m_object->GetGeometry());
	}
}
