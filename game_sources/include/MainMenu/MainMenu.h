#pragma once

#include "General/Entity.h"

class MainMenu : public Entity, public enable_shared_from_this<MainMenu>
{
public:
	void Initialize(shared_ptr<ResourceHandler> resources, shared_ptr<InputController> input);

	void ProcessInput() override;
	void Update(size_t dt) override;

	shared_ptr<InputController> GetController() const { return m_input.lock(); }
	shared_ptr<ResourceHandler> GetResources() const { return m_resources.lock(); }

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	vector<shared_ptr<Entity>>			m_entities;
	
	weak_ptr<InputController>			m_input;
	weak_ptr<ResourceHandler>			m_resources;
};
