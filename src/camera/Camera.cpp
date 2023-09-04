#include "Camera.h"

Camera* Camera::s_instance = nullptr;

Camera::Camera()
{
    m_view_box = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    m_target = nullptr;
    m_position = Vector2D(0, 0);
}

void Camera::Update(float dt)
{
    m_view_box.x = m_target->X - SCREEN_WIDTH/2; //the camera is centered around the player.
    m_view_box.y = m_target->Y - SCREEN_HEIGHT/2;

    if(m_view_box.x < 0)
    {
        m_view_box.x = 0;
    }

    if(m_view_box.y < 0)
    {
        m_view_box.y = 0;
    }

    if(m_view_box.x > (SCREEN_WIDTH + m_view_box.x)) //it works but i didn't understand this part.
    {
        m_view_box.x = (SCREEN_WIDTH + m_view_box.x);
    }

    if(m_view_box.y > (SCREEN_HEIGHT - m_view_box.y)) //for now, we don't want to change the y axis of the camera
    {
        m_view_box.y = (SCREEN_HEIGHT - m_view_box.y);
    }

    if(m_view_box.x > SCREEN_WIDTH * LEVEL_BORDER) // if the view_box (player) tries to escape the borders of the level, the camera scrolling is stopped.
    {
        m_view_box.x = SCREEN_WIDTH * LEVEL_BORDER;
    }

    m_position = Vector2D(m_view_box.x, m_view_box.y); //m_position is a vector that will be used in other parts of the code to adjust the camera.
}
