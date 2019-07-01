#include "stdafx_game.h"

#include "GameObjectManager.h"
#include "GameObjectGroup.h"
#include "GameObject.h"

/*
	TODO:
		1. I need to manage order of singleton objects deleting
*/

int WinMain(int argc, char **argv)
{
	auto root = GameObjectManager::instance()->CreateGameObject("root", nullptr);
	{
		auto child_1 = GameObjectManager::instance()->CreateGameObject("child_l1_n1", root);
		auto child_2 = GameObjectManager::instance()->CreateGameObject("child_l1_n2", child_1);
		{
			auto child_3 = GameObjectManager::instance()->CreateGameObject("child_l2_n1", child_2);
			auto child_4 = GameObjectManager::instance()->CreateGameObject("child_l2_n2", child_2);
		}

		child_1->GetGroupToChange()->Detach(child_2);
		child_2->DetachParent();

		root->GetGroupToChange()->Attach(child_2);
	}
	
	GameObjectManager::instance()->DeleteGameObject(root);

	return 0;
}
