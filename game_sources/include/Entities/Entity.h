#pragma once

class GameObject;

namespace Entities
{
	
class Entity
{
public:
	virtual ~Entity() = default;
	
	virtual void ProcessInput() {}
	virtual void Update(size_t dt) {}
	
	virtual GameObject * GetGameObject() const = 0;
};

}