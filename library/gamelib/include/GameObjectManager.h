#pragma once
#include "Singleton.h"

class GameObject;

class GameObjectManager : public Singleton<GameObjectManager>
{
	friend class Singleton<GameObjectManager>;
	~GameObjectManager();

public:

	GameObject * CreateGameObject();
	void DeleteGameObject(GameObject *);

private:

};