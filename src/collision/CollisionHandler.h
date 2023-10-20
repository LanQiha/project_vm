#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include <SDL.h>

#include "GameMap.h"
#include "Layers.h"
#include "MapHandler.h"
#include "engine.h"
#include "TextureManager.h"

class CollisionHandler
{
    public:

        inline static CollisionHandler* get_instance()
        {
            return s_instance = (s_instance != nullptr)? s_instance : new CollisionHandler;
        }

        bool MapCollision_BottomTile(SDL_Rect game_object);
        bool MapCollision_RightTile(SDL_Rect game_object);
        bool MapCollision_LeftTile(SDL_Rect game_object);
        bool MapCollision_TopTile(SDL_Rect game_object);
        bool EntityCollision(SDL_Rect game_object_a, SDL_Rect game_object_b);

    private:
        CollisionHandler();
        static CollisionHandler* s_instance;
        CollisionHandler* collision_wall;

        TileMap m_collision_map;
        TileLayer* m_collision_layer;
};

#endif // COLLISIONHANDLER_H
