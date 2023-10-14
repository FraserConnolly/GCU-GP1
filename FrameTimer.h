#pragma once

#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>
#include <Windows.h>

class FrameTimer
{
public:

    FrameTimer();
    void start();
    void restart();
    float elapsedMilliseconds();
    float elapsedSeconds();

private:

    LARGE_INTEGER StartingTime, EndingTime, ElapsedMicroseconds;
    LARGE_INTEGER Frequency;

};
