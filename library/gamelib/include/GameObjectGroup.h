#pragma once

class GameObject;

class GameObjectGroup
{
public:
	~GameObjectGroup();

	void Attach(GameObject * newChild);
	void Detach(GameObject * child);
	
	GameObject * FindChild(const string & name) const;
	GameObject * FindChildRec(const string & name) const;

private:
	set<GameObject *>	m_children;
};
