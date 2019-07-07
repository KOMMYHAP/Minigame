#include "stdafx_game.h"

#include "SingletonManager.h"
#include "LogMessageManager.h"

#include "GameObjectManager.h"
#include "GameObjectGroup.h"
#include "GameObject.h"

int WinMain(int argc, char **argv)
{
	SingletonManager singletonSequence;
	singletonSequence.DeleteFirst(GameObjectManager::Instance());
	singletonSequence.DeleteLast(LogMessageManager::Instance());

	auto root = GameObjectManager::Instance()->CreateGameObject("root", nullptr);
	{
		auto child_1 = GameObjectManager::Instance()->CreateGameObject("child_l1_n1", root);
		auto child_2 = GameObjectManager::Instance()->CreateGameObject("child_l1_n2", child_1);
		{
			auto child_3 = GameObjectManager::Instance()->CreateGameObject("child_l2_n1", child_2);
			auto child_4 = GameObjectManager::Instance()->CreateGameObject("child_l2_n2", child_2);
		}

		child_1->GetGroupToChange()->Detach(child_2);
		child_2->DetachParent();

		root->GetGroupToChange()->Attach(child_2);
	}
	
	GameObjectManager::Instance()->DeleteGameObject(root);

	return 0;
}
