#pragma once

#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>
#include <Windows.h>

class FrameTimer
{
public:

    FrameTimer ( );
    void start ( );
    void restart ( );
    float elapsedMilliseconds ( );
    float elapsedSeconds ( );

private:

    LARGE_INTEGER m_frequency;
    LARGE_INTEGER m_startingTime;
    LARGE_INTEGER m_endingTime;
    LARGE_INTEGER m_elapsedMicroseconds;

};
