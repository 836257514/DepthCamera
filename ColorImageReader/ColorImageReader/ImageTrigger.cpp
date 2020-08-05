#include "ImageTrigger.h"
#include <astra_core\capi\astra_core.h>
#include <iostream>

ImageTrigger::ImageTrigger() : m_isRunning(false)
{
}

void ImageTrigger::start()
{
	if (m_isRunning)
	{
		return;
	}
	
	m_isRunning = true;
	m_thread = thread(&ImageTrigger::continue_reading, this);
}

void ImageTrigger::stop()
{
	m_isRunning = false;
	m_thread.join();
}

void ImageTrigger::continue_reading()
{
	try
	{
		while (m_isRunning)
		{
			astra_update();
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	}
	catch (exception ex)
	{
		cout << ex.what() << endl;
	}
}