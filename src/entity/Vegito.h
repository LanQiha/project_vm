#ifndef VEGITO_H
#define VEGITO_H

#include <SDL.h>


#include "TextureManager.h"
#include "RigidBody.h"
#include "Animation.h"
#include "Collider.h"
#include "SpiritAnimation.h"
#include "SequenceAnimation.h"

#include "Player.h"

#include "RigidBody.h"

const int MOVING_FORWARD = 1;
const int MOVING_BACKWARD = -1;

const float FLY_FORCE = 3.0f;


class Vegito : public Player
{
    public:
        Vegito(Properties* props);

        virtual void draw();
        virtual void update(float dt);
        virtual void clean();

    private:
        void AnimationState();

    private:
        bool m_is_grounded;
        bool m_is_flying;

        bool m_is_jumping;
        bool m_is_falling;

        bool m_is_attacking;

        SpiritAnimation* m_animation;
        Collider* m_collider;
        RigidBody* m_rigid_body;

        SequenceAnimation* m_sequence_animation;

        Vector2D m_last_safe_position;
};

#endif // VEGITO_H
