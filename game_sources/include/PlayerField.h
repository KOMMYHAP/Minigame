#pragma once

#include "Entity.h"

class Player;

class PlayerField : public Entity, public enable_shared_from_this<PlayerField>
{
public:
	PlayerField();

	void Initialize(shared_ptr<InputController> controller, shared_ptr<ResourceHandler> resources, shared_ptr<sf::Window> window);

	void ProcessInput() override;
	void Update(float dt) override;
	
	const sf::FloatRect & GetBorder() const { return m_border; }
	bool IsInBorders(const sf::Vector2f & position) const;

	shared_ptr<InputController> GetController() const { return m_input.lock(); }
	shared_ptr<ResourceHandler> GetResources() const { return m_resources.lock(); }

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::FloatRect						m_border;

	unique_ptr<Player>					m_player;
	sf::Vector2f						m_playerStartPos;

	weak_ptr<InputController>			m_input;
	weak_ptr<ResourceHandler>			m_resources;
};
