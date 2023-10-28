#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

const int TARGET_FPS = 60;
const float TARGET_DELTA_TIME = 1.5f;


class Timer
{
    public:
        inline static Timer* GetInstance()
        {
            return s_instance = (s_instance != nullptr)? s_instance : new Timer();
        }

        inline float GetDeltaTime(){return m_delta_time;}

        void Tick();

    private:
        Timer();
        static Timer* s_instance;

        float m_delta_time;
        float m_last_time;
};

#endif // TIMER_H
