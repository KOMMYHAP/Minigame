#pragma once

#include "Entity.h"

class VideoSource;

class Video : public Entity
{
public:
	Video();

	void Initialize(const VideoSource * source, bool isLooped = false);
	
	void Pause() { m_onPause = true; }
	void Play() { m_onPause = false; }
	void Stop();

	void Update(float dt) override;
	void SetSize(sf::Vector2u size);

	sf::FloatRect GetBBox() const override;

private:
	void UpdateTexture() const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	float						m_currentMs			{0.0f};

	float						m_msOnFrame			{0.0f};
	bool						m_onPause			{true};
	bool						m_isLooped			{false};

	size_t						m_frameIndexToShow	{0};
	const VideoSource *			m_source			{nullptr};
	
	unique_ptr<sf::Texture>		m_texture;
};
