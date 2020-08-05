#pragma once
#include <thread>
using namespace std;

class ImageTrigger
{
public:
	ImageTrigger();
	void start();
	void stop();
private:
	thread m_thread;
	bool m_isRunning;
	void continue_reading();
};

