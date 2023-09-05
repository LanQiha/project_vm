#include "Event.h"

Event* Event::s_instance = nullptr; //initialize the ptr as a nullptr

const SDL_Scancode FORWARD = SDL_SCANCODE_E;
const SDL_Scancode BACKWARD = SDL_SCANCODE_Q;

void Event::Listen()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT : //it closes the program if the user clicks on the cross
                Engine::GetInstance()->Quit();
                break;
            case SDL_KEYDOWN : //call the KeyDown() function when the user presses a key
                KeyDown();
                break;
            case SDL_KEYUP : //call the KeyUp() function when the user releases a key
                KeyUp();
                break;
        }
    }
}

bool Event::GetKeyDown(SDL_Scancode key)
{
    if(m_key_state[key]==1)
        return true;

    return false;
}

void Event::KeyUp()
{
    m_key_state = SDL_GetKeyboardState(nullptr);
}

void Event::KeyDown()
{
    m_key_state = SDL_GetKeyboardState(nullptr);
}

//get the axis forward or backward
int Event::GetAxis()
{
    if(GetKeyDown(FORWARD))
        return 1;

    if(GetKeyDown(BACKWARD))
        return -1;

    return 0;
}
