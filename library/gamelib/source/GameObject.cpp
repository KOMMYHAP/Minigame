#include "basic_defs.h"

#include "LogMessageManager.h"

#include "GameObject.h"
#include "GameObjectGroup.h"
#include "GameObjectManager.h"
#include "GameObjectGeometry.h"

GameObject::GameObject(GameObject * parent /* = nullptr */)
	: GameObject("", parent)
{
}

GameObject::GameObject(const string& name, GameObject* parent /* = nullptr */)
	: m_parent(parent)
	, m_geometry(make_unique<GameObjectGeometry>())
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
