#pragma once

class VideoSource
{
public:
	VideoSource();

	bool LoadFromFile(const string & name);

	sf::Vector2u GetSize() const { return m_size; }

	size_t GetFramesNumber() const { return m_frames.size(); }
	size_t GetFPS() const { return m_fps; }
	const sf::Image & GetFrame(size_t number) const;

private:
	vector<sf::Image>		m_frames;
	sf::Vector2u			m_size;
	size_t					m_fps {0};
};