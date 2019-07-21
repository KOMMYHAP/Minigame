#include "stdafx_game.h"

#include "Cutscene/Cutscene.h"

void Cutscene::Initialize(shared_ptr<GameSceneCallback> callback)
{
	m_callback = callback;
}

void Cutscene::OnStartScene()
{
	
}

void Cutscene::OnEndScene()
{
}
