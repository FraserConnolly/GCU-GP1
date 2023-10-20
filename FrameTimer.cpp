#include "FrameTimer.h"

FrameTimer::FrameTimer() 
	: m_startingTime(), 
	m_endingTime(), 
	m_elapsedMicroseconds(), 
	m_frequency()
{
	QueryPerformanceFrequency(&m_frequency);
	start();
}

void FrameTimer::start()
{
	QueryPerformanceCounter(&m_startingTime);
}

void FrameTimer::restart()
{
	QueryPerformanceCounter(&m_endingTime);
	m_elapsedMicroseconds.QuadPart = m_endingTime.QuadPart - m_startingTime.QuadPart;

	//
	// We now have the elapsed number of ticks, along with the
	// number of ticks-per-second. We use these values
	// to convert to the number of elapsed microseconds.
	// To guard against loss-of-precision, we convert
	// to microseconds *before* dividing by ticks-per-second.
	//

	m_elapsedMicroseconds.QuadPart *= 1000000;
	m_elapsedMicroseconds.QuadPart /= m_frequency.QuadPart;
	m_startingTime = m_endingTime;
}

float FrameTimer::elapsedMilliseconds()
{
	return ( float ) m_elapsedMicroseconds.QuadPart / 1000.0f;
}

float FrameTimer::elapsedSeconds()
{
	return ( float ) m_elapsedMicroseconds.QuadPart / 1000000.0f;
}