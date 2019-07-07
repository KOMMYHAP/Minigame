#pragma once
#include "Singleton.h"

enum class InputKey
{
	W, A, S, D,
	ARROW_LEFT, ARROW_RIGHT, ARROW_TOP, ARROW_BOTTOM,
	LEFT_CLICK
};

class InputController : public Singleton<InputController>
{
public:
	void ProcessInput();
	
	bool IsPressed(InputKey key) const;

private:
	map<InputKey, bool>		m_keys;
	
};
