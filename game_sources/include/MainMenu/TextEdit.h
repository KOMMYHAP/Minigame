#pragma once
#include "General/Entity.h"

class TextEdit : public Entity
{
public:
	TextEdit();

	void ProcessInput() override;
	void Update(float dt) override;

	sf::FloatRect GetBBox() const override;
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void UpdateText() const;

	string						m_text;
	unique_ptr<sf::Text>		m_textField;
};
