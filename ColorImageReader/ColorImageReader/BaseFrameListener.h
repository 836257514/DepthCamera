#pragma once
#include <astra/astra.hpp>
#include "CommonStructure.h"
using namespace astra;

template<typename TCallback>
class BaseFrameListener : public FrameListener
{
public:
    BaseFrameListener(TCallback callBack)
    {
        m_callBack = callBack;
    }

    virtual ~BaseFrameListener() = default;
    virtual void on_frame_ready(StreamReader& reader, Frame& frame) = 0;
protected:
    TCallback m_callBack;
    image_info m_imageInfo;
};

