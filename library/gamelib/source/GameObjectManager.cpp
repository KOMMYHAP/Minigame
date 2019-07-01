#include "basic_defs.h"

#include "GameObjectManager.h"
#include "GameObject.h"

GameObjectManager::~GameObjectManager()
{

}

GameObject* GameObjectManager::CreateGameObject(const string& name, GameObject * parent /* = nullptr */)
{
	return new GameObject(name, parent);
}

void GameObjectManager::DeleteGameObject(GameObject * object)
{
	if (object)
	{
		delete object;
	}
}

