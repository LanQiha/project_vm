#include "Timer.h"

Timer* Timer::s_instance = nullptr;

Timer::Timer()
{
    m_delta_time = 0.0f;
    m_last_time = 0.0f;
}

void Timer::Tick()
{

    m_delta_time = (SDL_GetTicks() - m_last_time)*(TARGET_FPS/1000.0f);

    if(m_delta_time > TARGET_DELTA_TIME)
    {
        m_delta_time = TARGET_DELTA_TIME;
    }

    m_last_time = SDL_GetTicks();
}
