#pragma once

class Entity;

enum class GameEvent
{
	TOUCH_PLAYER,
	TOUCH_GROUND,
	END_OF_LIFE,
	CUTSCENE_TRIGGER,
	CUTSCENE_CHARACTER_MOVING_COMPLETED,
	COUNT
};

class GameListener
{
public:
	virtual ~GameListener() = default;

	virtual void Call(GameEvent event, shared_ptr<Entity> sender) = 0;
};
