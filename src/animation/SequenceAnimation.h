#ifndef SEQUENCEANIMATION_H
#define SEQUENCEANIMATION_H

#include <string>
#include <vector>
#include <map>

#include <SDL2/SDL.h>

#include "Animation.h"

struct Sequence
{
    int animation_speed;
    int frame_count;
    int width, height;
    std::vector <std::string> texture_id;
};

class SequenceAnimation : public Animation
{
    public:
        SequenceAnimation(bool repeat = true){}

        virtual void Update(float dt);
        void Draw(int X, int Y, SDL_RendererFlip flip, float scale_X, float scale_Y);

        void SetCurrentSequence(std::string sequence_id); //change the state of the player form run to jump for exemple
        void Parse(std::string source);

        inline void SetRepeat(bool repeat){m_repeat = repeat;}

    private:
        Sequence m_current_sequence;
        std::map <std::string, Sequence> m_sequence_map;
};

#endif // SEQUENCEANIMATION_H
