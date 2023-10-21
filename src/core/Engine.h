#ifndef ENGINE_H
#define ENGINE_H/0

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "Camera.h"
#include "Vegito.h"
#include "ObjectFactory.h"
#include "TextureManager.h"
#include "GameMap.h"
#include "MapHandler.h"
#include "GameObject.h"
#include "Transform.h"
#include "Vector2D.h"
#include "SoundsManager.h"
#include "Timer.h"

#define SCREEN_WIDTH 960
#define SCREEN_HEIGHT 640

// This is a C++ include guard, ensuring the header file is included only once.
// It prevents multiple inclusion of the same header, avoiding compilation errors.

class Engine
{
    public:
        // It is a singleton class, which means there is only one instance of this class.
        // The GetInstance() method is used to access that instance.
        inline static Engine* GetInstance() {
            return s_instance = (s_instance != nullptr)? s_instance : new Engine();
        }

        // Function that initializes the engine.
        bool Init();

        // Function to render objects on the screen.
        void Render();

        // Function to update the game logic.
        void Update();

        // Function to handle events such as keyboard input.
        void Event();

        // Function to clean up dynamic variables.
        void Clean();

        // Function to quit and clean up the engine.
        void Quit();

        // Inline method to check if the engine is running.
        inline bool GetIsRunning(){return m_isRunning;}

        // Inline methods to get the SDL window and renderer.
        inline SDL_Window* GetWindow(){return m_window;}
        inline SDL_Renderer* GetRenderer(){return m_renderer;}

        // Inline method to get the game map.
        inline GameMap* GetMap(){return m_levelMap;}

    private:
        Engine(){}; // Private constructor to enforce singleton pattern.
        ~Engine(); // Destructor to clean up resources when the engine is destroyed.
        static Engine* s_instance; // Static instance of the engine.

        bool m_isRunning; // Flag to determine if the game is running.
        SDL_Window* m_window; // SDL window for rendering.
        SDL_Renderer* m_renderer; // SDL renderer for rendering graphics.
        GameMap* m_levelMap; // Game map object for managing the game world.
};

#endif // ENGINE_H
