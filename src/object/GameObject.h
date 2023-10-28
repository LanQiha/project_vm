#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SDL2/SDL.h>

#include "Object.h"
#include "Transform.h"


struct Properties
{
    Properties(std::string textureId, float x, float y, int width, int height, SDL_RendererFlip flip = SDL_FLIP_NONE)
    {
        TextureId = textureId;
        X = x;
        Y = y;
        Width = width;
        Height = height;
        Flip = flip;
    }

    int Width, Height;
    std::string TextureId;
    float X, Y;
    SDL_RendererFlip Flip;
};

class GameObject : public Object
{
    public:
        GameObject(Properties* props) : m_texture_id(props->TextureId), m_width(props->Width), m_height(props->Height),
        m_flip(props->Flip) {
            m_transform = new Transform(props->X, props-> Y);

            float px = props->X + props->Width/2;
            float py = props->Y + props->Height/2;
            m_origin = new Vector2D(px, py);
        }

        inline Vector2D* get_origin(){return m_origin;}

        virtual void Draw(){};
        virtual void Update(float dt){};
        virtual void Clean(){};

    protected:
        Vector2D* m_origin;
        std::string m_texture_id;
        int m_width, m_height;
        SDL_RendererFlip m_flip;
        Transform* m_transform;
};

#endif // GAMEOBJECT_H
