#include "basic_defs.h"

#include "GameObject.h"
#include "GameObjectGroup.h"
#include "GameObjectManager.h"

GameObjectGroup::~GameObjectGroup()
{
	for (auto child : m_children)
	{
		GameObjectManager::instance()->DeleteGameObject(child);
	}
}

void GameObjectGroup::Attach(GameObject* newChild)
{
	assert(newChild != nullptr);
	auto [it, success] = m_children.insert(newChild);
	assert(success && "Trying to attach already existing child!");
}

void GameObjectGroup::Detach(GameObject* child)
{
	auto it = m_children.find(child);
	assert(it != m_children.end() && "Trying to detach non existing child!");
	m_children.erase(it);
}

GameObject * GameObjectGroup::FindChild(const string& name) const
{
	for (auto child : m_children)
	{
		if (child->GetName() == name)
		{
			return child;
		}
	}
}

GameObject * GameObjectGroup::FindChildRec(const string& name) const
{
	if (auto child = FindChild(name))
	{
		return child;
	}

	for (auto child : m_children)
	{
		return child->GetGroup()->FindChildRec(name);
	}

	return nullptr;
}
