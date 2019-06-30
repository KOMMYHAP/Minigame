#pragma once

class GameObjectGroup;
class GameObjectGeometry;

class GameObject
{
	friend class GameObjectManager;
	~GameObject();

public:
	GameObject();

	void DetachParent();
	void SetParent(GameObject *parent);
	
	GameObjectGeometry * GetGeometryToChange() { return m_geometry.get(); }
	GameObjectGeometry const * GetGeometry() const { return m_geometry.get(); }
	
	GameObjectGroup * GetGroupToChange() { return m_group ? m_group.get() : nullptr; }
	GameObjectGroup const * GetGroup() const { return m_group ? m_group.get() : nullptr; }

	auto && GetName() const { return m_name; }

private:
	unique_ptr<GameObjectGroup>		m_group;
	GameObject *					m_parent {nullptr};
	unique_ptr<GameObjectGeometry>	m_geometry;

	string							m_name;
};