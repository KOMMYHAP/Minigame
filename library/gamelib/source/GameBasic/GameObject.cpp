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

	UpdateGlobalGeometry();

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
	UpdateGlobalGeometry();
}

void GameObject::SetParent(GameObject* parent)
{
	m_parent = parent;
	UpdateGlobalGeometry();
}

void GameObject::SetGeometry(const sf::Transform & transform)
{
	m_matrixLocal = transform;
	UpdateGlobalGeometry();
}

void GameObject::UpdateGlobalGeometry()
{
	if (auto parent = GetParent())
	{
		auto matrix = parent->GetGlobalGeometry();
		m_matrixGlobal = matrix * m_matrixLocal;
	}
	else
	{
		m_matrixGlobal = m_matrixLocal;
	}

	auto && children = GetGroupToChange()->GetChildrenToChange();
	for (auto child : children)
	{
		child->UpdateGlobalGeometry();
	}
}
