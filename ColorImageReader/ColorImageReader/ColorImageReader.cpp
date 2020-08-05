// ColorImageReader.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <astra/astra.hpp>
#include <cstdio>
#include <iostream>
#include <key_handler.h>
#include <thread>
#include <mutex>
#include <ctime>
#include <sstream>
#include "CommonStructure.h"
#include "DepthImageFrameListener.h"
#include "Utility.h"
#include "CImg.h"
#include "ColorImageFrameListener.h"
#include "ImageTrigger.h"

using namespace cimg_library_suffixed;
using namespace astra;
using namespace std;

void on_rgb_frame_updated(const RgbPixel* bufferPtr, image_info& imageInfo);
void on_depth_frame_updated(const int16_t* bufferPtr, image_info& imageInfo);
unique_ptr<ColorImageFrameListener> add_color_stream(astra::StreamReader& reader);
unique_ptr<DepthImageFrameListener> add_depth_stream(astra::StreamReader& reader);

int main(int argc, char** argv)
{
	astra::terminate();
	astra::initialize();

	set_key_handler();

	astra::StreamSet streamSet;
	astra::StreamReader reader = streamSet.create_reader();
	unique_ptr<ColorImageFrameListener> colorListener = add_color_stream(reader);
	unique_ptr<DepthImageFrameListener> depthListener = add_depth_stream(reader);
	ImageTrigger imageTrigger;
	imageTrigger.start();
	try
	{
		cout << "enter quit to exit." << endl;
		string inputString;
		do
		{
			std::cin >> inputString;
		} while (inputString != "quit");
	}
	catch (std::exception ex)
	{
		std::cout << ex.what() << std::endl;
	}

	imageTrigger.stop();
	reader.remove_listener(*colorListener);
	reader.remove_listener(*depthListener);
	astra::terminate();
	system("pause");
}

unique_ptr<ColorImageFrameListener> add_color_stream(astra::StreamReader& reader)
{
	unique_ptr<ColorImageFrameListener> listener(new ColorImageFrameListener(on_rgb_frame_updated));
	reader.stream<astra::ColorStream>().start();
	reader.add_listener(*listener);
	return listener;
}

unique_ptr<DepthImageFrameListener> add_depth_stream(astra::StreamReader& reader)
{
	unique_ptr<DepthImageFrameListener> listener(new DepthImageFrameListener(on_depth_frame_updated));
	astra::DepthStream depthStream =reader.stream<astra::DepthStream>();
	depthStream.start();
	char serialnumber[256];
	depthStream.serial_number(serialnumber, 256);
	reader.add_listener(*listener);
	return listener;
}

void on_depth_frame_updated(const int16_t* bufferPtr, image_info& depthImageInfo)
{
	CImg<uint16_t> img(depthImageInfo.width, depthImageInfo.height, 1, 1);
	for (int row = 0; row < depthImageInfo.height; ++row)
	{
		int offset = row * depthImageInfo.width;
		for (int col = 0; col < depthImageInfo.width; ++col)
		{
			*(img.data(col, row, 0, 0)) = bufferPtr[offset + col];
		}
	}

	const char* const filename = "C:\\2.bmp";
	img.save_bmp(filename);
}

void on_rgb_frame_updated(const RgbPixel* bufferPtr, image_info& rgbImageInfo)
{
	clock_t startTime = clock();
	CImg<uint8_t> img(rgbImageInfo.width, rgbImageInfo.height, 1, 3);
	for (int row = 0; row < rgbImageInfo.height; ++row)
	{
		int offset = row * rgbImageInfo.width;
		for (int col = 0; col < rgbImageInfo.width; ++col)
		{
			int index = offset + col;
			*(img.data(col, row, 0, 0)) = bufferPtr[index].r;
			*(img.data(col, row, 0, 1)) = bufferPtr[index].g;
			*(img.data(col, row, 0, 2)) = bufferPtr[index].b;
		}
	}

	long passTime = clock() - startTime;
	
	OutputDebugStringA(Utility::ltos(passTime, "spend time").c_str());
	const char* const filename = "C:\\1.bmp";
	
	img.save_bmp(filename);

}