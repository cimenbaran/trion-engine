#pragma once
#include <cstdint>

class Time
{

public:

    // Once per frame
    static void Update(); 
    
    // Time between last 2 frames (seconds)
    static float DeltaTime();
    
    // Total time elapsed since application started (seconds)
    static float TimeSinceStart();
    
    // Total rendered frames since application start
    static uint64_t FrameCount();

private:
    static void InitIfNeeded();


private:
    static bool s_initialized;
    static float s_deltaTime;
    static float s_timeSinceStart;
    static uint64_t s_frameCount;
};