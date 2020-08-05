#pragma once

#include <Memory>
#include <astra/astra.hpp>
using namespace astra;

class MySampleFrameListener2 : public FrameListener
{
private:
	using buffer_ptr = std::unique_ptr<RgbPixel[]>;
	buffer_ptr buffer_;
	unsigned int lastWidth_;
	unsigned int lastHeight_;

public:
	virtual void on_frame_ready(astra::StreamReader& reader, Frame& frame) override;
};