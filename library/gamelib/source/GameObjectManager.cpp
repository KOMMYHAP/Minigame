#include "basic_defs.h"

#include "GameObjectManager.h"
#include "GameObject.h"

GameObjectManager::~GameObjectManager()
{

}

GameObject* GameObjectManager::CreateGameObject()
{
	return new GameObject();
}

void GameObjectManager::DeleteGameObject(GameObject * object)
{
	delete object;
}

