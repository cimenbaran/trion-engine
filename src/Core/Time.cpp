#include "Core/Time.h"
#include <chrono>

namespace
{
    using Clock = std::chrono::steady_clock;
    using TimePoint = Clock::time_point;

    TimePoint g_startTime;
    TimePoint g_lastFrameTime;
}

bool Time::s_initialized = false;
float Time::s_deltaTime = 0.0f;
float Time::s_timeSinceStart = 0.0f;
uint64_t Time::s_frameCount = 0;

void Time::InitIfNeeded()
{
    if (s_initialized)
        return;

    g_startTime = Clock::now();
    g_lastFrameTime = g_startTime;
    s_initialized = true;
}

void Time::Update()
{
    InitIfNeeded();

    const TimePoint now = Clock::now();

    const std::chrono::duration<float> delta = now - g_lastFrameTime;
    s_deltaTime = delta.count();
    g_lastFrameTime = now;

    const std::chrono::duration<float> total = now - g_startTime;
    s_timeSinceStart = total.count();

    ++s_frameCount;
}

float Time::DeltaTime()
{
    return s_deltaTime;
}

float Time::TimeSinceStart()
{
    return s_timeSinceStart;
}

uint64_t Time::FrameCount()
{
    return s_frameCount;
}
