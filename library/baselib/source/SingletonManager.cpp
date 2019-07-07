#include "basic_defs.h"

#include "SingletonManager.h"
#include "Singleton.h"

SingletonManager::~SingletonManager()
{
	for (auto obj : m_objects)
	{
		delete obj;
	}
}

void SingletonManager::DeleteFirst(SingletonBase* what)
{
	RemoveFromQueue(what);

	m_objects.insert(m_objects.begin(), what);
}

void SingletonManager::DeleteAfter(SingletonBase* whatToDelete, SingletonBase* afterWhat)
{
	RemoveFromQueue(whatToDelete);

	auto it = std::find(m_objects.begin(), m_objects.end(), afterWhat);
	if (it == m_objects.end())
	{
		DeleteLast(afterWhat);
		DeleteLast(whatToDelete);
		return;
	}

	m_objects.insert(it + 1, whatToDelete);	
}

void SingletonManager::DeleteBefore(SingletonBase* whatToDelete, SingletonBase* beforeWhat)
{
	RemoveFromQueue(whatToDelete);

	auto it = std::find(m_objects.begin(), m_objects.end(), beforeWhat);
	if (it == m_objects.end())
	{	
		DeleteLast(whatToDelete);
		DeleteLast(beforeWhat);
		return;
	}

	m_objects.insert(it, whatToDelete);	
}

void SingletonManager::DeleteLast(SingletonBase* what)
{
	RemoveFromQueue(what);

	m_objects.push_back(what);
}

void SingletonManager::RemoveFromQueue(SingletonBase* what)
{
	auto jt = std::find(m_objects.begin(), m_objects.end(), what);
	if (jt != m_objects.end())
	{
		m_objects.erase(jt);
	}
}
