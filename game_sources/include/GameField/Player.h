#pragma once

#include "General/Entity.h"

class PlayField;

class Player : public Entity
{
public:
	Player();

	void Initialize(shared_ptr<PlayField> playField);

	void ProcessInput() override;
	void Update(float dt) override;

	sf::FloatRect GetBBox() const override;

	shared_ptr<PlayField> GetPlayField() const { return m_field.lock(); }

private:
	struct JumpHelper
	{
		const float		acceleraionUp			{2500};
		const float		acceleraionDown 		{3500};
		const float		jumpHeight				{100.f};

		float	startY	{0.f};
		float	endY	{0.f};

		bool	isFlyingUp	{true};
	};

	void CreateJump();
	void UpdateJump(float dt);
	void UpdateMoving(float dt);

	bool LoadAll();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	const sf::Vector2f					m_initialVelocity	{500.0f, 0.f};

	bool								m_jumpIsPressed {false};
	bool								m_isStopping	{false};

	sf::Vector2f						m_velocity;
	unique_ptr<JumpHelper>				m_jump;

	sf::Sprite							m_sprite;

	weak_ptr<PlayField>					m_field;
};