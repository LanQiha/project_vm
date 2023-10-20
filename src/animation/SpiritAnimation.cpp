#include "SpiritAnimation.h"

#include <SDL.h>

#include "TextureManager.h"

void SpiritAnimation::Update(float dt)
{
    m_current_frame = (SDL_GetTicks() / m_animation_speed) % m_frame_count;
}

void SpiritAnimation::Draw(int x, int y, int spirit_width, int spirit_height, float scale_X = 1, float scale_Y = 1)
{
    TextureManager::GetInstance()->DrawFrame(m_texture_id, x, y, spirit_width, spirit_height, m_current_frame, m_flip, scale_X, scale_Y);
}

void SpiritAnimation::SetSpiritAnimation(std::string texture_id, int spirit_row, int frame_count, int animation_speed, SDL_RendererFlip flip = SDL_FLIP_NONE)
{
    m_texture_id = texture_id;
    m_spirit_row = spirit_row;
    m_frame_count = frame_count;
    m_animation_speed = animation_speed;
    m_flip = flip;
}
