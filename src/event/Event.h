#ifndef EVENT_H
#define EVENT_H

#include <SDL2/SDL.h>

#include "Engine.h"


class Event
{
    public:
        //Event is a singleton class
        static Event* GetInstance()
        {return s_instance = (s_instance != nullptr)? s_instance : new Event();}

        void Listen(); //function that detects if a player press a key on the keyboard or wants to close the program
        bool GetKeyDown(SDL_Scancode key); //detects which key was pressed
        int GetAxis();

    private:
        static Event* s_instance; //the instance of this class is private
        Event(){} //Event's constructor

        void KeyUp();
        void KeyDown();

        const Uint8* m_key_state;
};

#endif // EVENT_H
