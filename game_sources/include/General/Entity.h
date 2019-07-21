#pragma once

class InputController;
class ResourceHandler;

class Entity : public sf::Transformable, public sf::Drawable
{
public:
	~Entity() override = default;

	virtual void ProcessInput() {}
	virtual void Update(float dt) {}

	virtual sf::FloatRect GetBBox() const = 0;
};