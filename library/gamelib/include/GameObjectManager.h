#pragma once
#include "Singleton.h"

class GameObject;

class GameObjectManager : public Singleton<GameObjectManager>
{
	friend class Singleton<GameObjectManager>;
	~GameObjectManager();

public:
	GameObject * CreateGameObject(const string& name, GameObject * parent);
	void DeleteGameObject(GameObject *);

private:
	size_t		m_objectsNumber {0};
};