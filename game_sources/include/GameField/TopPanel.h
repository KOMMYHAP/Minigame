#pragma once

#include "General/Entity.h"
#include "General/GameListener.h"

class HealthPanel;
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
	sf::FloatRect GetBBox() const override;

private:
	void CallEvent(GameEvent event, shared_ptr<Entity> sender);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	shared_ptr<ScorePanel>				m_scores;
	shared_ptr<HealthPanel>				m_health;

	vector<shared_ptr<GameListener>>	m_listeners;
	weak_ptr<PlayField>					m_playfield;
};

class HealthPanel : public Entity
{
public:
	HealthPanel();

	void Initialize(shared_ptr<ResourceHandler> resources);

	void OnMissingSnowlake();
	void OnTouchingHealthPack();

	sf::FloatRect GetBBox() const override;

	int GetLifes() const { return m_lifes; }

private:
	void UpdateText() const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	const char *			m_format	{"%03d"};
	const int				m_maxLifes	{999};
	int						m_lifes		{10};

	sf::Sprite				m_sprite;
	unique_ptr<sf::Text>	m_text;
};

class ScorePanel : public Entity
{
public:
	ScorePanel();

	void Initialize(shared_ptr<ResourceHandler> resources);
	
	void OnMiss();
	void OnTouch();
	bool IsEnoughScoresForWin() const { return GetScores() >= m_scoresForWin; }
	
	size_t GetScores()			const	{ return m_number; }
	size_t GeNextScoresNumber() const	{ return m_nextNumber; }
	size_t GetCurrentCoef()		const	{ return m_numberInARow; }

	sf::FloatRect GetBBox() const override;

private:
	void UpdateText() const;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	
	size_t const				m_minBonus		{5};
	size_t const				m_maxCoef		{999};
	size_t const				m_maxNumber		{999999999ULL};
	size_t const				m_scoresForWin	{999999999ULL};
	const char *				m_format		{"Scores: %08llu \nMultiplier:  %03llu "};

	size_t						m_nextNumber	{0};
	size_t						m_numberInARow	{0};
	size_t						m_number		{0};

	unique_ptr<sf::Text>		m_text;
};
