#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include <vector>

#include <SDL2/SDL.h>

#include "GameObject.h"

using TextureIdList = std::vector<std::string>;

enum ButtonSate {NORMAL=0, HOVER=1, PRESSED=2};


class Button : public GameObject
{
    public:
        Button(int x, int y, void (*callback)(), TextureIdList texture_id_list);
        virtual ~Button();

        virtual void Draw();
        virtual void Update(float dt);
        virtual void Clean();

    private:
        void (*m_callback)();
        SDL_Rect m_shape;
        TextureIdList m_texture_id_list;
        bool m_release;
};

#endif // BUTTON_H
