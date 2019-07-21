#pragma once
#include "General/Entity.h"
#include "General/GameListener.h"

class Character	: public Entity, public enable_shared_from_this<Character>
{
public:
	Character();

	void Initialize(shared_ptr<ResourceHandler> resources);

	void Update(float dt) override;
	sf::FloatRect GetBBox() const override;

	void Subscribe(shared_ptr<GameListener> listener) { m_listeners.emplace_back(std::move(listener)); }

	const sf::Vector2f & GetEndPosition() const { return m_endPos; }

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void CallAll(GameEvent event, shared_ptr<Entity> sender) const;
	
	const sf::Vector2f					m_startPos				{0.0f, 420.f};
	const sf::Vector2f					m_endPos				{195.0f, 335.f};
	const float							m_startScale			{0.2f};
	const float							m_endScale				{0.35f};

	float								m_dt					{0.0f};
	float								m_timeToMove			{10.0f};

	sf::Vector2f						m_velocity				{(m_endPos - m_startPos) / m_timeToMove};
	float								m_scale					{m_startScale};
	float								m_angularVelocity		{5.f};
	float								m_maxAngle				{3.f};

	sf::Vector2u						m_spriteSize;
	sf::Sprite							m_sprite;
	vector<shared_ptr<GameListener>>	m_listeners;
};
