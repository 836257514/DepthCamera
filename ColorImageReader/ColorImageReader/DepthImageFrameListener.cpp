#include "DepthImageFrameListener.h"
#include "Utility.h"
#include <windows.h>

void DepthImageFrameListener::on_frame_ready(astra::StreamReader& reader, Frame& frame)
{
	const astra::DepthFrame depthFrame = frame.get<astra::DepthFrame>();
	if (depthFrame.is_valid())
	{
		auto depthStream = reader.stream<astra::DepthStream>();
		int width = depthFrame.width();
		int height = depthFrame.height();
		if (width != m_imageInfo.width || height != m_imageInfo.height)
		{
			m_imageInfo.width = width;
			m_imageInfo.height = height;
			m_imageInfo.length = depthFrame.byte_length();
		}

		m_callBack(depthFrame.data(), m_imageInfo);

		//const CoordinateMapper mapper = depthStream.coordinateMapper();
		//float worldX, worldY, worldZ;		
		//mapper.convert_depth_to_world(width / 2.0f, height / 2.0f, middle, worldX, worldY, worldZ);
	}
}