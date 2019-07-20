#pragma once

#include "General/Entity.h"

class PlayField;

class Player : public Entity
{
public:
	Player();

	void Initialize(shared_ptr<PlayField> playField);

	void ProcessInput() override;
	void Update(size_t dt) override;

	sf::FloatRect GetBBox() const;

	shared_ptr<PlayField> GetPlayField() const { return m_field.lock(); }

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

	bool LoadAll();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	const sf::Vector2f					m_maxVelocity;

	bool								m_jumpIsPressed {false};
	bool								m_isStopping {false};

	sf::Vector2f						m_velocity;
	unique_ptr<JumpHelper>				m_jump;

	sf::Sprite							m_sprite;

	weak_ptr<PlayField>					m_field;
};