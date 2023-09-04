#ifndef COLLIDER_H
#define COLLIDER_H


class Collider
{
    public:
        inline SDL_Rect GetBoxCollider(){return m_box_collider;}

        inline void SetBuffer(int x, int y, int w, int h){m_buffer = {x, y, w, h};}

        void SetBoxCollider(int x, int y, int w, int h)
        {
            m_box_collider = {x -= m_buffer.x, y -= m_buffer.y, w -= m_buffer.w, h -= m_buffer.h};
        }

    private:
        SDL_Rect m_box_collider;
        SDL_Rect m_buffer;
};

#endif // COLLIDER_H
