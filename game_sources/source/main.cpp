#include "stdafx_game.h"

#include "GameObjectManager.h"
#include "GameObject.h"

int WinMain(int argc, char **argv)
{
	auto root = GameObjectManager::instance()->CreateGameObject("root");
	{
		auto child_1 = GameObjectManager::instance()->CreateGameObject("child_l1_n1", root);
		auto child_2 = GameObjectManager::instance()->CreateGameObject("child_l1_n2", root);
		{
			auto child_3 = GameObjectManager::instance()->CreateGameObject("child_l2_n1", child_1);
			auto child_4 = GameObjectManager::instance()->CreateGameObject("child_l2_n2", child_1);

			// GameObjectManager::instance()->DeleteGameObject(child_4);
			// GameObjectManager::instance()->DeleteGameObject(child_3);
		}

		// GameObjectManager::instance()->DeleteGameObject(child_2);
		// GameObjectManager::instance()->DeleteGameObject(child_1);
	}
	
	GameObjectManager::instance()->DeleteGameObject(root);

	return 0;
}
