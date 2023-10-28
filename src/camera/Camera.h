#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>

#include "Vector2D.h"
#include "engine.h"

const float LEVEL_BORDER = 1.5f; //this value shall be changed.


class Camera
{
    public:
        inline static Camera* GetInstance()
        {return s_instance = (s_instance != nullptr)? s_instance : new Camera();}

        inline SDL_Rect GetViewBox() {return m_view_box;}
        inline Vector2D GetPosition() {return m_position;}
        inline void SetTarget(Vector2D* target) {m_target = target;}

        void Update(float dt);

    private:
        Camera();
        static Camera* s_instance;

        Vector2D* m_target; //m_target will target the player so it can focus the camera on it.
        Vector2D m_position; //m_position's coordinates will be used to set the camera -> m_view_box.

        SDL_Rect m_view_box; //the view_box is a rectangle.
};

#endif // CAMERA_H
