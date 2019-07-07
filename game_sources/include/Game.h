#pragma once

class GameState;

class Game
{
public:

private:
	vector<unique_ptr<GameState>>	m_states;
};