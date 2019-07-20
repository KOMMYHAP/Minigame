#pragma once

#include "Entity.h"
#include "GameListener.h"

class PlayField;
class ScorePanel;

class TopPanel : public Entity, public GameListener
{
public:
	TopPanel();

	void Initialize(shared_ptr<PlayField> playfield);

	void Call(GameEvent event, shared_ptr<Entity> sender) override;
	void Subscribe(shared_ptr<GameListener> listener) { m_listeners.emplace_back(std::move(listener)); }

	shared_ptr<PlayField> GetPlayfield() const { return m_playfield.lock(); };

private:
	void CallEvent(GameEvent event, shared_ptr<Entity> sender);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	shared_ptr<ScorePanel>				m_scores;

	vector<shared_ptr<GameListener>>	m_listeners;
	weak_ptr<PlayField>					m_playfield;
};

class ScorePanel : public Entity
{
public:
	ScorePanel();

	void Initialize(shared_ptr<ResourceHandler> resources);
	
	void OnMiss();
	void OnTouch();
	
	size_t GetScores()			const	{ return m_number; }
	size_t GeNextScoresNumber() const	{ return m_nextNumber; }
	size_t GetCurrentCoef()		const	{ return m_numberInARow; }

	sf::FloatRect GetBbox() const;

private:
	void UpdateText() const;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
	size_t const				m_minBonus		{6};
	size_t const				m_maxCoef		{100};
	size_t const				m_maxNumber		{999999999ULL};
	const char *				m_format		{"Scores: %08llu \nMultiplier:  %03llu "};

	size_t						m_nextNumber	{0};
	size_t						m_numberInARow	{0};
	size_t						m_number		{0};

	unique_ptr<sf::Text>		m_text;
};
