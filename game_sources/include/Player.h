#pragma once

#include "Entity.h"

class PlayerField;

class Player : public Entity
{
public:
	Player();

	void Initialize(shared_ptr<PlayerField> playerField);

	void ProcessInput() override;
	void Update(float dt) override;

	sf::FloatRect GetSpriteSize() const;

	shared_ptr<PlayerField> GetPlayerField() const { return m_field.lock(); }

private:
	struct JumpHelper
	{
		const float		upCoef					{0.95f};
		const float		downCoef				{1.2f};
		const float		initFlyingDownSpeed		{10.0f};
		const float		m_jumpHeight			{100.f};

		float	startY	{0.f};
		float	endY	{0.f};

		bool	isFlyingUp	{true};
	};

	void CreateJump();
	void UpdateJump();
	void UpdateMoving();
	void MoveToBorder(const sf::Vector2f& invalidPos);

	bool LoadAll();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	const sf::Vector2f					m_maxVelocity;

	sf::Vector2f						m_velocity;
	unique_ptr<JumpHelper>				m_jump;

	sf::Sprite							m_sprite;

	weak_ptr<PlayerField>				m_field;
};