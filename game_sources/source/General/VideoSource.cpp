#include "stdafx_game.h"

#include "General/VideoSource.h"

#include "opencv2/videoio.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "LogMessageManager.h"

VideoSource::VideoSource()
{
}

bool VideoSource::LoadFromFile(const string & name)
{
	using namespace cv;

	VideoCapture capture(name);
	if (!capture.isOpened())
    {
		LOG_ERROR("Cannot load open file %1% for loading video!", name);
        return false;
    }

	m_size = {
		static_cast<sf::Uint32>(capture.get(CAP_PROP_FRAME_WIDTH)),
        static_cast<sf::Uint32>(capture.get(CAP_PROP_FRAME_HEIGHT))
	};

	auto frameCount = static_cast<int>(capture.get(CAP_PROP_FRAME_COUNT));
	m_frames.reserve(frameCount);

	m_fps = static_cast<size_t>(capture.get(CAP_PROP_FPS));

	Mat frameReference;
	vector<uchar> buffer;

	while (true)
	{
		capture >> frameReference;
		if (frameReference.empty())
		{
			break;
		}

		buffer.resize(frameReference.total() * 4);
		Mat frameRGBA(frameReference.size(), CV_8UC4, buffer.data());
		cvtColor(frameReference, frameRGBA, COLOR_BGR2RGBA, 4);

		m_frames.emplace_back();
		m_frames.back().create(m_size.x, m_size.y, buffer.data());
	}

	return true;
}

const sf::Image& VideoSource::GetFrame(size_t number) const
{
	assert(number < m_frames.size());
	if (number < m_frames.size())
	{
		return m_frames[number];
	}
	LOG_ERROR("Attempting to access an frame outside the range!");
	static sf::Image stub;
	return stub;
}
