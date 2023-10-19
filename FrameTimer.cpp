#include "FrameTimer.h"

FrameTimer::FrameTimer()
{
	QueryPerformanceFrequency(& this -> Frequency);
	start();
}

void FrameTimer::start()
{
	QueryPerformanceCounter(& this -> StartingTime);
}


void FrameTimer::restart()
{
	QueryPerformanceCounter(&EndingTime);
	this -> ElapsedMicroseconds.QuadPart = this -> EndingTime.QuadPart - this -> StartingTime.QuadPart;

	//
	// We now have the elapsed number of ticks, along with the
	// number of ticks-per-second. We use these values
	// to convert to the number of elapsed microseconds.
	// To guard against loss-of-precision, we convert
	// to microseconds *before* dividing by ticks-per-second.
	//

	this -> ElapsedMicroseconds.QuadPart *= 1000000;
	this -> ElapsedMicroseconds.QuadPart /= this -> Frequency.QuadPart;
	this -> StartingTime = EndingTime;
}

float FrameTimer::elapsedMilliseconds()
{
	return this -> ElapsedMicroseconds.QuadPart / 1000.0;
}

float FrameTimer::elapsedSeconds()
{
	return this -> ElapsedMicroseconds.QuadPart / 1000000.0;
}