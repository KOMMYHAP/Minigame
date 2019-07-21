#pragma once
#include "General/Entity.h"


class Character	: public Entity
{
public:
	Character();

	void Initialize(shared_ptr<ResourceHandler> resources);

	void Update(float dt) override;
	sf::FloatRect GetBBox() const override;

private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	sf::Vector2f				m_startPos				{0.0f, 420.f};
	sf::Vector2f				m_endPos				{180.0f, 320.f};
	float						m_startScale			{0.2f};
	float						m_endScale				{0.35f};

	float						m_dt					{0.0f};
	float						m_timeToMove			{10.0f};

	sf::Vector2f				m_velocity				{(m_endPos - m_startPos) / m_timeToMove};
	float						m_scale					{m_startScale};
	float						m_angularVelocity		{15.f};
	float						m_maxAngle				{5.f};

	sf::Vector2u				m_spriteSize;
	sf::Sprite					m_sprite;
};
