#pragma once
#include <Memory>
#include <astra/astra.hpp>
#include "CommonStructure.h"
#include "BaseFrameListener.h"
using namespace astra;

typedef void(*DepthFrameUpdated)(const int16_t*, image_info&);

class DepthImageFrameListener : public BaseFrameListener<DepthFrameUpdated>
{
public:
	DepthImageFrameListener(DepthFrameUpdated callback) : BaseFrameListener(callback) {}
	virtual void on_frame_ready(astra::StreamReader& reader, Frame& frame) override;
};

