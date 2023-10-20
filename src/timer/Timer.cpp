#include "Timer.h"

// Initialization of the single instance of the class Timer.
Timer* Timer::s_instance = nullptr;

// Initialization of the private variables.
Timer::Timer()
{
    m_deltaTime = 0.0f;
    m_lastTime = 0.0f;
}

// Deletes the s_instance pointer.
Timer::~Timer()
{
    s_instance = nullptr;
    delete s_instance;
}

// Updates m_deltaTime.
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

