#include "stdafx_game.h"

#include "Cutscene/Cutscene.h"
#include "Cutscene/Character.h"

#include "General/ResourceHandler.h"
#include "General/Video.h"

Cutscene::Cutscene()
{
}

void Cutscene::Initialize(shared_ptr<GameSceneCallback> callback)
{
	m_callback = callback;
}

void Cutscene::OnStartScene()
{
	auto resources = m_callback->GetResources();
	
	auto background = make_shared<Video>();
	auto success = resources->LoadVideo(Videoes::CUTSCENE, "Resources/cutscene.mp4");
	assert(success);
	if (auto ptr = resources->GetVideo(Videoes::CUTSCENE))
	{
		background->Initialize(ptr, true);
		background->SetSize(m_callback->GetRenderWindow()->getSize());
		background->Play();
		m_background = background;
	}

	auto character = make_shared<Character>();
	{
		character->Initialize(resources);
	}
	
	m_entities.push_back(background);
	m_entities.push_back(character);
}

void Cutscene::OnEndScene()
{
	if (auto video = m_background.lock())
	{
		video->Stop();
	}
}

void Cutscene::ProcessInput()
{
	for (auto && entity : m_entities)
	{
		entity->ProcessInput();
	}
}

void Cutscene::Update(float dt)
{
	for (auto && entity : m_entities)
	{
		entity->Update(dt);
	}
}

void Cutscene::Draw(sf::RenderWindow& window)
{
	sf::RenderStates states;
	for (auto && entity : m_entities)
	{
		window.draw(*entity, states);
	}
}
