#pragma once

class GameObject;

class GameObjectGroup
{
public:
	explicit GameObjectGroup(GameObject * parent);
	~GameObjectGroup();

	void Attach(GameObject * newChild);
	void Detach(GameObject * child);

	GameObject * FindChild(const string & name) const;
	GameObject * FindChildRec(const string & name) const;
	
	const set<GameObject *> & GetChildren() const { return m_children; }
	set<GameObject *> & GetChildrenToChange() { return m_children; }

private:
	set<GameObject *>		m_children;
	GameObject *			m_parent;
};
