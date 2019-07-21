#pragma once

#include "General/Entity.h"
#include "General/GameListener.h"

class TextBox : public Entity, public GameListener
{
public:
	TextBox();

	void Initialize(shared_ptr<ResourceHandler> resources);

	void Update(float dt) override;

	void Call(GameEvent event, shared_ptr<Entity> sender) override;

	sf::FloatRect GetBBox() const override;

private:
	using Phrase = vector<std::wstring>;

	void SplitOnPhrases(const wchar_t * message);

	void UpdateText() const;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	vector<Phrase>				m_sourcePhrases;
	size_t						m_phraseIndex		{0};
	size_t						m_phraseToShow		{0};

	const float					m_symbolsPerSecond	{10.0f};
	const size_t				m_maxLineInPhrase	{5};
	float						m_symbolWidth		{0.0f};
	size_t						m_maxSymbolsInPhrase{0};
	size_t						m_maxSymbolsInRow	{0};

	float						m_speed				{0.0f};
	float						m_delayToNextPhrase {0.0f};

	bool						m_onPause			{true};
	bool						m_isHidden			{true};

	unique_ptr<sf::Text>		m_text;
	sf::RectangleShape			m_background;
};
