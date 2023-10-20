#ifndef SPIRITANIMATION_H
#define SPIRITANIMATION_H

#include <string>
#include <SDL.h>

#include "Animation.h"


class SpiritAnimation : public Animation
{
    public:
        SpiritAnimation(bool repeat = true){}

        virtual void Update(float dt);
        void Draw(int x, int y, int spirit_width, int spirit_height, float scale_X, float scale_Y);
        void SetSpiritAnimation(std::string texture_id, int spirit_row, int frame_count, int animation_speed, SDL_RendererFlip flip);

        inline int GetCurrentFrame(){return m_current_frame;}

    private:
        int m_spirit_row;
        int m_frame_count;
        int m_animation_speed;
        std::string m_texture_id;
        SDL_RendererFlip m_flip;
};

#endif // SPIRITANIMATION_H
