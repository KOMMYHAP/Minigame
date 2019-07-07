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

	auto jt = std::find(m_objects.begin(), m_objects.end(), whatToDelete);
	if (jt != m_objects.end())
	{
		m_objects.erase(jt);
	}

	auto it = std::find(m_objects.begin(), m_objects.end(), afterWhat);

	assert(it != m_objects.end() && "Cannot find specified place to delete after it!");
	if (it == m_objects.end())
	{
		return;
	}

	m_objects.insert(it + 1, whatToDelete);	
}

void SingletonManager::DeleteBefore(SingletonBase* whatToDelete, SingletonBase* beforeWhat)
{
	RemoveFromQueue(whatToDelete);

	auto it = std::find(m_objects.begin(), m_objects.end(), beforeWhat);

	assert(it != m_objects.end() && "Cannot find specified place to delete before it!");
	if (it == m_objects.end())
	{
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
