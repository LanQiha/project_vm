#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

#include "tinyxml.h"

#include <map>

#include "engine.h"


class TextureManager
{
    public:
        static TextureManager* GetInstance()
        {return s_instance = (s_instance != nullptr)? s_instance : new TextureManager();}

        bool Load(std::string id, std::string filename);
        bool ParseTexture(std::string source);
        void Drop(std::string id);
        void Clean();

        void Draw(std::string id, int x, int y, int width, int height, float scale_X, float scale_Y, float scroll_ratio, SDL_RendererFlip flip);
        void DrawTile(std::string tileset_id, int tile_size, int x, int y, int row, int frame, SDL_RendererFlip flip = SDL_FLIP_NONE);

        void DrawFrame(std::string id, int x, int y, int width, int height, int frame, SDL_RendererFlip flip, float scale_X, float scale_Y);

    private:
        TextureManager() {}
        static TextureManager* s_instance;

        std::map <std::string, SDL_Texture*> m_texture_map;
};

#endif // TEXTUREMANAGER_H
