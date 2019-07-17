#pragma once

class InputController;
class ResourceHandler;

class Entity : public sf::Transformable, public sf::Drawable
{
public:
	virtual void ProcessInput() {}
	virtual void Update(float dt) {}	
};