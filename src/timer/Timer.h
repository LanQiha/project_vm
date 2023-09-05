#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

const int TARGET_FPS = 60;
const float TARGET_DELTA_TIME = 1.5f;

class Timer
{
    public:
        //Timer is a singleton class, the GetInstance() function returns the single instance of this class
        inline static Timer* GetInstance() {
            return s_instance = (s_instance != nullptr)? s_instance : new Timer();
        }

        inline float GetDeltaTime(){return m_deltaTime;}

        void Tick();

    private:
        Timer();
        static Timer* s_instance;

        float m_deltaTime;
        float m_lastTime;
};

#endif // TIMER_H
