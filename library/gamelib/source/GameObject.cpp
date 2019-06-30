#include "basic_defs.h"

#include "GameObjectGeometry.h"
#include "GameObjectGroup.h"
#include "GameObject.h"

GameObject::~GameObject()
{
}

GameObject::GameObject()
	: m_geometry(make_unique<GameObjectGeometry>())
{
}

void GameObject::DetachParent()
{
	if (m_parent)
	{
		m_parent->GetGroupToChange()->Detach(this);
		m_parent = nullptr;
	}
}

void GameObject::SetParent(GameObject* parent)
{
	if (m_parent)
	{
		DetachParent();
	}

	if (parent)
	{
		parent->GetGroupToChange()->Attach(this);
	}

	m_parent = parent;
}
