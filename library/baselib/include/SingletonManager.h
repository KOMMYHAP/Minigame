#pragma once

class SingletonBase;

class SingletonManager
{
public:
	~SingletonManager();

	void DeleteFirst(SingletonBase * what);
	void DeleteAfter(SingletonBase * whatToDelete, SingletonBase * afterWhat);
	void DeleteBefore(SingletonBase * whatToDelete, SingletonBase * beforeWhat);
	void DeleteLast(SingletonBase * what);

private:
	void RemoveFromQueue(SingletonBase * what);

	vector<SingletonBase *>		m_objects;
};