#include "ColorImageFrameListener.h"

void ColorImageFrameListener::on_frame_ready(astra::StreamReader& reader, Frame& frame)
{
	const astra::ColorFrame colorFrame = frame.get<astra::ColorFrame>();
	if (colorFrame.is_valid())
	{
		int width = colorFrame.width();
		int height = colorFrame.height();
		int frameIndex = colorFrame.frame_index();

		if (width != m_imageInfo.width || height != m_imageInfo.height) {
			m_imageInfo.height = height;
			m_imageInfo.width = width;
			m_imageInfo.length = colorFrame.byte_length();
		}

		m_callBack(colorFrame.data(), m_imageInfo);
	}
}