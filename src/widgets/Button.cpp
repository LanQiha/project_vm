#include "Button.h"

Button::~Button()
{
    Button::Clean();
}

void Button::Draw()
{

}

void Button::Update(float dt)
{

}

void Button::Clean()
{
    m_texture_id.clear();
    m_texture_id.shrink_to_fit();
}
