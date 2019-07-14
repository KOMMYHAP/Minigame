#include "stdafx_gamelib.h"

#include "LogMessageManager.h"

#include "GameBasic/GameObject.h"
#include "GameBasic/GameObjectGroup.h"
#include "GameBasic/GameObjectManager.h"

GameObject::GameObject(GameObject * parent /* = nullptr */)
	: GameObject("", parent)
{
}

GameObject::GameObject(const string& name, GameObject* parent /* = nullptr */)
	: m_parent(parent)
	, m_name(name)
{
	m_group = make_unique<GameObjectGroup>(this);

	if (parent)
	{
		parent->GetGroupToChange()->Attach(this);
	}

	LOG_MESSAGE("GameObject \"%s\" created.", name);
}

GameObject::~GameObject()
{
	if (m_parent)
	{
		if (m_parent->GetGroup())
		{
			m_parent->GetGroupToChange()->Detach(this);	
		}
		m_parent = nullptr;
	}

	m_group.reset();

	LOG_MESSAGE("GameObject \"%s\" destroyed.", m_name);
}

void GameObject::DetachParent()
{
	m_parent = nullptr;
}

void GameObject::SetParent(GameObject* parent)
{
	m_parent = parent;
}
