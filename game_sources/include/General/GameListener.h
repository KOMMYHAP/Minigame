#pragma once

class Entity;

enum class GameEvent
{
	TOUCH_PLAYER,
	TOUCH_GROUND,
	CUTSCENE_TRIGGER,
	END_OF_LIFE,
	COUNT
};

class GameListener
{
public:
	virtual ~GameListener() = default;

	virtual void Call(GameEvent event, shared_ptr<Entity> sender) = 0;
};
