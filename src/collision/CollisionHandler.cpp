#include "CollisionHandler.h"


CollisionHandler* CollisionHandler::s_instance = nullptr;

CollisionHandler::CollisionHandler()
{
    m_collision_layer = (TileLayer*)Engine::GetInstance()->GetMap()->get_map_layers().front();
    m_collision_map = m_collision_layer->get_tile_map();
}

bool CollisionHandler::MapCollision_BottomTile(SDL_Rect game_object)
{
    int tile_size = 32;
    int row_count = 20;
    int col_count = 75;

    int left_tile = game_object.x / tile_size;
    int right_tile = (game_object.x + game_object.w) / tile_size;

    //std::cout << left_tile << " " << right_tile << std::endl;

    int top_tile = game_object.y / tile_size;
    int bottom_tile = (game_object.y + game_object.h) / tile_size;

    //std::cout << top_tile << " " << bottom_tile << std::endl;

    /*if(left_tile < 0)
    {
        left_tile = 0;
    }

    if(right_tile > col_count)
    {
        right_tile = col_count;
    }

    if(top_tile < 0)
    {
        top_tile = 0;
    }

    if(bottom_tile > row_count)
    {
        bottom_tile = row_count;
    }*/

    for(int i = left_tile + 1; i < right_tile; ++i)
    {
        if(m_collision_map[bottom_tile][i] > 0)
        {
            return true;
        }
    }
    return false;
}

/* bool CollisionHandler::MapCollision_RightTile(SDL_Rect game_object)
{
    int tile_size = 32;
    int row_count = 20;
    int col_count = 75;

    int left_tile = game_object.x / tile_size;
    int right_tile = (game_object.x + game_object.w) / tile_size;

    //std::cout << left_tile << " " << right_tile << std::endl;

    int top_tile = game_object.y / tile_size;
    int bottom_tile = (game_object.y + game_object.h) / tile_size;

    //std::cout << top_tile << " " << bottom_tile << std::endl;

    if(left_tile < 0)
    {
        left_tile = 0;
    }

    if(right_tile > col_count)
    {
        right_tile = col_count;
    }

    if(top_tile < 0)
    {
        top_tile = 0;
    }

    if(bottom_tile > row_count)
    {
        bottom_tile = row_count;
    }

    for(int j = top_tile; j < bottom_tile; ++j)
    {
        if(m_collision_map[j][right_tile] > 0)
        {
                return true;
        }
    }
    return false;
}

bool CollisionHandler::MapCollision_LeftTile(SDL_Rect game_object)
{
    int tile_size = 32;
    int row_count = 20;
    int col_count = 75;

    int left_tile = game_object.x / tile_size;
    int right_tile = (game_object.x + game_object.w) / tile_size;

    //std::cout << left_tile << " " << right_tile << std::endl;

    int top_tile = game_object.y / tile_size;
    int bottom_tile = (game_object.y + game_object.h) / tile_size;

    //std::cout << top_tile << " " << bottom_tile << std::endl;

    if(left_tile < 0)
    {
        left_tile = 0;
    }

    if(right_tile > col_count)
    {
        right_tile = col_count;
    }

    if(top_tile < 0)
    {
        top_tile = 0;
    }

    if(bottom_tile > row_count)
    {
        bottom_tile = row_count;
    }

    for(int j = top_tile; j < bottom_tile; ++j)
    {
        if(m_collision_map[j][left_tile] > 0)
        {
                return true;
        }
    }
    return false;
}

bool CollisionHandler::MapCollision_TopTile(SDL_Rect game_object)
{
    int tile_size = 32;
    int row_count = 20;
    int col_count = 75;

    int left_tile = game_object.x / tile_size;
    int right_tile = (game_object.x + game_object.w) / tile_size;

    //std::cout << left_tile << " " << right_tile << std::endl;

    int top_tile = game_object.y / tile_size;
    int bottom_tile = (game_object.y + game_object.h) / tile_size;

    //std::cout << top_tile << " " << bottom_tile << std::endl;

    if(left_tile < 0)
    {
        left_tile = 0;
    }

    if(right_tile > col_count)
    {
        right_tile = col_count;
    }

    if(top_tile < 0)
    {
        top_tile = 0;
    }

    if(bottom_tile > row_count)
    {
        bottom_tile = row_count;
    }

    for(int i = left_tile + 1; i < right_tile; ++i)
    {
        if(m_collision_map[top_tile][i] > 0)
        {
                return true;
        }
    }
    return false;
} */

bool CollisionHandler::EntityCollision(SDL_Rect game_object_a, SDL_Rect game_object_b)
{
    bool x_overlaps = (game_object_a.x < game_object_b.x + game_object_b.w) && (game_object_b.x < game_object_a.x + game_object_a.w);
    bool y_overlaps = (game_object_a.y < game_object_b.y + game_object_b.h) && (game_object_b.y < game_object_a.y + game_object_a.h);
    return (x_overlaps && y_overlaps);
}
