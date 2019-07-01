#include "basic_defs.h"

#include "GameObjectManager.h"
#include "GameObject.h"
#include "LogMessageManager.h"

GameObjectManager::~GameObjectManager()
{
	assert(m_objectsNumber == 0);
}

GameObject* GameObjectManager::CreateGameObject(const string& name, GameObject * parent)
{
	++m_objectsNumber;
	return new GameObject(name, parent);
}

void GameObjectManager::DeleteGameObject(GameObject * object)
{
	if (object)
	{
		--m_objectsNumber;
		delete object;
	}
}

