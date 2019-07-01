#include "basic_defs.h"

#include "GameObject.h"
#include "GameObjectGroup.h"
#include "GameObjectManager.h"

GameObjectGroup::~GameObjectGroup()
{
	if (m_children.empty())
	{
		return;
	}

	vector<GameObject *> objects {m_children.begin(), m_children.end()};
	for (auto object : objects)
	{
		object->DetachParent();
	}
	m_parent = nullptr;

	for (auto object : objects)
	{
		GameObjectManager::instance()->DeleteGameObject(object);
	}
}

GameObjectGroup::GameObjectGroup(GameObject* parent)
	: m_parent(parent)
{
	assert(parent != nullptr && "Group of objects must have parent!");
}

void GameObjectGroup::Attach(GameObject* newChild)
{
	assert(newChild != nullptr && newChild->GetParent() == m_parent);

	if (newChild != nullptr && newChild->GetParent() == m_parent)
	{
		auto [it, success] = m_children.insert(newChild);
		assert(success && "Trying to attach already existing child!");	
	}
}

void GameObjectGroup::Detach(GameObject* child)
{
	assert(child && child->GetParent() == m_parent);

	if (child && child->GetParent() == m_parent)
	{
		auto it = m_children.find(child);
		m_children.erase(it);
	}
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

	return nullptr;
}

GameObject * GameObjectGroup::FindChildRec(const string& name) const
{
	queue<GameObject *> queue;
	for (auto child : m_children)
	{
		queue.push(child);
	}

	while (!queue.empty())
	{
		auto obj = queue.front();
		queue.pop();

		if (obj->GetName() == name)
		{
			return obj;
		}

		auto && children = obj->GetGroup()->GetChildren();
		for (auto child : children)
		{
			queue.push(child);
		}
	}

	return nullptr;
}
