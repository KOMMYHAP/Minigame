#pragma once

#include "Entity.h"

class Player;
class SnowflakeHandler;

class PlayField : public Entity, public enable_shared_from_this<PlayField>
{
public:
	PlayField();
	~PlayField();

	void Initialize(shared_ptr<InputController> controller, shared_ptr<ResourceHandler> resources, shared_ptr<sf::Window> window);

	void ProcessInput() override;
	void Update(size_t dt) override;
	
	// bool IsInBorders(const sf::Vector2f & position) const;
	sf::FloatRect GetBBox() const;
	sf::Vector2f MoveToHorizontalBorder(const sf::FloatRect & size) const;

	shared_ptr<InputController> GetController() const { return m_input.lock(); }
	shared_ptr<ResourceHandler> GetResources() const { return m_resources.lock(); }
	shared_ptr<std::mt19937>	GetRandom() const { return m_random; }

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	vector<shared_ptr<Entity>>			m_entities;

	sf::Sprite							m_sprite;

	shared_ptr<std::mt19937>			m_random;
	weak_ptr<InputController>			m_input;
	weak_ptr<ResourceHandler>			m_resources;
};
