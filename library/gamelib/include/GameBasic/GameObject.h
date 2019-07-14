#pragma once

class GameObjectGroup;

class GameObject
{
	friend class GameObjectManager;
	~GameObject();

public:
	explicit GameObject(GameObject * parent = nullptr);
	explicit GameObject(const string & name, GameObject * parent = nullptr);

	void DetachParent();
	void SetParent(GameObject *parent);
	
	GameObject * GetParentToChange() { return m_parent; }
	GameObject const * GetParent() const { return m_parent; }
	
	sf::Transform & GetGeometryToChange() { return m_geometry; }
	sf::Transform const & GetGeometry() const { return m_geometry; }
	
	GameObjectGroup * GetGroupToChange() { return m_group.get(); }
	GameObjectGroup const * GetGroup() const { return m_group.get(); }

	void SetName(const string & name) { m_name = name; }
	const string & GetName() const { return m_name; }

private:
	unique_ptr<GameObjectGroup>		m_group;
	GameObject *					m_parent	{nullptr};
	sf::Transform					m_geometry;

	string							m_name;
};