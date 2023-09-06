#include "Timer.h"

// Initialization of the instance of the class Timer.
Timer* Timer::s_instance = nullptr;

Timer::Timer()
{
    // Initialization of the private variables.
    m_deltaTime = 0.0f;
    m_lastTime = 0.0f;
}

void Timer::Tick()
{
    // Determines how much time has elapsed since the last frame.
    m_deltaTime = (SDL_GetTicks() - m_lastTime)*(TARGET_FPS/1000.0f);

    // Prevents m_deltaTime from becoming too high.
    if(m_deltaTime > TARGET_DELTA_TIME) {
        m_deltaTime = TARGET_DELTA_TIME;
    }

    m_lastTime = SDL_GetTicks();
}

// The SDL_GetTicks() function returns the number of milliseconds that have passed since SDL was initialized.

