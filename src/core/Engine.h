#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "GameMap.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640


class Engine
{
    public:
        static Engine* GetInstance() //it is a singleton class
        {return s_instance = (s_instance != nullptr)? s_instance : new Engine();}

        bool Init(); //function that initialize the engine

        void Render(); //function that render stuff on the screen
        void Update(); //function that update the game
        void Event(); //function that takes care of the keyboard system
        void Clean(); //function that cleans dynamics variables
        void Quit();

        inline bool GetIsRunning(){return m_is_running;}
        inline SDL_Window* GetWindow(){return m_window;}
        inline SDL_Renderer* GetRenderer(){return m_renderer;}
        inline GameMap* GetMap(){return m_level_map;}

    private:
        Engine(){};
        static Engine* s_instance;

        bool m_is_running;
        SDL_Window* m_window;
        SDL_Renderer* m_renderer;
        GameMap* m_level_map;
};

#endif // ENGINE_H
