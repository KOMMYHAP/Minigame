#include "stdafx_game.h"

#include "General/Video.h"
#include "General/VideoSource.h"

Video::Video()
	: m_texture(make_unique<sf::Texture>())
{
}

void Video::Initialize(const VideoSource* source, bool isLooped)
{
	m_source = source;
	m_msOnFrame = 1.0f / m_source->GetFPS();
	m_isLooped = isLooped;
}

void Video::Stop()
{
	m_onPause = true;
	m_currentMs = 0.0;
	m_frameIndexToShow = 0;
}

void Video::Update(float dt)
{
	if (m_onPause)
	{
		return;
	}

	m_currentMs += dt;
	m_frameIndexToShow = static_cast<size_t>(std::floor(m_currentMs / m_msOnFrame));

	if (m_frameIndexToShow >= m_source->GetFramesNumber())
	{
		m_currentMs = 0;
		m_frameIndexToShow = 0;
		m_onPause = !m_isLooped;
	}
}

void Video::SetSize(sf::Vector2u size)
{
	auto sourceSize = m_source->GetSize();
	setScale(float(size.x) / sourceSize.x, float(size.y) / sourceSize.y);
}

sf::FloatRect Video::GetBBox() const
{
	if (m_source)
	{
		sf::FloatRect rect = {0, 0, float(m_source->GetSize().x), float(m_source->GetSize().y)};
		return getTransform().transformRect(rect);	
	}
	return {};
}

void Video::UpdateTexture() const
{
	auto && image = m_source->GetFrame(m_frameIndexToShow);
	assert(m_texture->loadFromImage(image));
}

void Video::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	UpdateTexture();
	states.transform.combine(getTransform());
	sf::Sprite sprite(*m_texture);
	target.draw(sprite, states);
}
