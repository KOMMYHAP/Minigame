#include "stdafx_gamelib.h"

#include "GameBasic/GameObject.h"
#include "GameBasic/GameObjectManager.h"
#include "LogMessageManager.h"

GameObjectManager::~GameObjectManager()
{
	if (m_objectsNumber != 0)
	{
		assert(m_objectsNumber == 0);
		LOG_ERROR("GameObjectManager destructor: %d objects are exist yet!");
	}
}

GameObject* GameObjectManager::Create(const string& name, GameObject * parent)
{
	++m_objectsNumber;
	return new GameObject(name, parent);
}

void GameObjectManager::Delete(GameObject * object)
{
	if (object)
	{
		--m_objectsNumber;
		delete object;
	}
}

