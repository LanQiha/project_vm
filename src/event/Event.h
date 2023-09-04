#ifndef EVENT_H
#define EVENT_H

#include <SDL2/SDL.h>

#include "Engine.h"


class Event
{
    public:
        static Event* GetInstance()
        {return s_instance = (s_instance != nullptr)? s_instance : new Event();}

        void Listen();
        bool GetKeyDown(SDL_Scancode key);
        int GetAxis();

    private:
        static Event* s_instance;
        Event(){}

        void KeyUp();
        void KeyDown();

        const Uint8* m_key_state;
};

#endif // EVENT_H
