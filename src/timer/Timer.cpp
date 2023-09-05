#include "Timer.h"

//initialization of the single instance of the class
Timer* Timer::s_instance = nullptr;

Timer::Timer()
{
    //initialization of the private variables
    m_deltaTime = 0.0f;
    m_lastTime = 0.0f;
}

void Timer::Tick()
{

    m_deltaTime = (SDL_GetTicks() - m_lastTime)*(TARGET_FPS/1000.0f);

    if(m_deltaTime > TARGET_DELTA_TIME) {
        m_deltaTime = TARGET_DELTA_TIME;
    }

    m_lastTime = SDL_GetTicks();
}
