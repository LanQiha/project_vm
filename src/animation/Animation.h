#ifndef ANIMATION_H
#define ANIMATION_H


class Animation
{
    public:
        Animation(bool repeat = true) : m_repeat(repeat) {m_end = false;}

        virtual void Update(float dt) = 0;
        inline bool GetEnd(){return m_end;}

    protected:
        int m_current_frame;
        bool m_repeat;
        bool m_end;
};

#endif // ANIMATION_H

