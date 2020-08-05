#pragma once
#include <Memory>
#include <astra/astra.hpp>
#include "CommonStructure.h"
#include "BaseFrameListener.h"
using namespace astra;

typedef void(*RgbFrameUpdated)(const RgbPixel*, image_info&);

class ColorImageFrameListener : public BaseFrameListener<RgbFrameUpdated>
{
public:
	ColorImageFrameListener(RgbFrameUpdated callBack) : BaseFrameListener(callBack) {}
	virtual void on_frame_ready(astra::StreamReader& reader, Frame& frame) override;
};