#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vector2D.h"
#include "Vegito.h"
#include <iostream>
#include "CollisionHandler.h"
#include "Collider.h"

#include "Event.h"


#define MASS 1.0f
#define GRAVITY 9.81f

const float FRICTION = 0.7f;
const float GRAVITY_FRICTION = 0.3f;

const int MOVING_UP = -1;
const float JUMP_TIME = 15.0f;
const float JUMP_FORCE = 5.0f;

//const int MOVING_FORWARD = 1;
const float DASH_TIME = 120.0f;
const float DASH_FORCE = 60.0f;

class RigidBody
{
    public:
        RigidBody(float mass = MASS, float gravity = GRAVITY){
            m_mass = mass;
            m_gravity = gravity;
        }

        inline void UnsetForce(){m_force = Vector2D(0, 0);}
        inline void UnsetForce_X(){m_force.X = 0;}
        inline void UnsetForce_Y(){m_force.Y = 0;}

        inline void SetForce_X(float force_X){m_force.X = force_X;}
        inline void SetForce_Y(float force_Y){m_force.Y = force_Y;}

        inline void ApplyForce_X(float force_X){m_force.X += force_X;}
        inline void ApplyForce_Y(float force_Y){m_force.Y += force_Y;}

        inline void ApplyVelocity_Y(float velocity_Y){m_velocity.Y += velocity_Y;}

        inline Vector2D GetPosition(){return m_position;}
        inline Vector2D GetVelocity(){return m_velocity;}
        inline Vector2D GetAcceleration(){return m_acceleration;}

        void SetState()
        {
            m_is_grounded = false;

            m_position = Vector2D(50, 250);
            m_velocity = Vector2D(0, 0);
            m_acceleration = Vector2D(0, 0);

            m_force = Vector2D(0, 0);

            m_jump_time = JUMP_TIME;

            m_dash_time = DASH_TIME;
        }

        void UpdateEntity(float dt, Collider* collider, Vector2D last_safe_position)
        {
            m_position = last_safe_position;

            SetForce_Y(GRAVITY * MASS * GRAVITY_FRICTION);
        }

        void UpdateCharacter(float dt, Collider* collider, Vector2D last_safe_position)
        {
            m_position = last_safe_position;

            SetForce_Y(GRAVITY * MASS * GRAVITY_FRICTION);

            CharacterJump(dt);
            EntityCollision(dt, collider);
            CharacterDash(dt);

            m_acceleration = (m_force / m_mass);
            m_velocity = (m_velocity + m_acceleration * dt ) * FRICTION;
            m_position = m_position + m_velocity * dt;
        }


    private:

        // UpdateEntity

        float m_mass;
        float m_gravity;

        Vector2D m_position;
        Vector2D m_velocity;
        Vector2D m_acceleration;

        Vector2D m_force;

        // UpdateCharacter

        bool m_is_grounded;
        bool m_is_jumping;

        float m_jump_time;

        float m_dash_time;

        bool CharacterJump(float dt)
        {
            if(Event::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_is_grounded)
            {
                m_is_jumping = true;

                ApplyVelocity_Y(MOVING_UP * JUMP_FORCE);
            }
            if(Event::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE) && m_is_jumping && m_jump_time > 0)
            {
                m_jump_time-=dt;

                ApplyVelocity_Y(MOVING_UP * JUMP_FORCE);

                return m_is_jumping;
            }
            else{
                m_is_jumping = false;

                m_jump_time = JUMP_TIME;

                return m_is_jumping;
            }
        }

        float dashCooldownTimer;

        void CharacterDash(float dt)
        {
            if (Event::GetInstance()->GetKeyDown(SDL_SCANCODE_CAPSLOCK) && Event::GetInstance()->GetKeyDown(SDL_SCANCODE_E))
            {
                if (dashCooldownTimer <= 0.0f)
                {
                    ApplyForce_X(DASH_FORCE);
                    dashCooldownTimer = DASH_TIME;
                }
            }

            if (Event::GetInstance()->GetKeyDown(SDL_SCANCODE_CAPSLOCK) && Event::GetInstance()->GetKeyDown(SDL_SCANCODE_Q))
            {
                if (dashCooldownTimer <= 0.0f)
                {
                    ApplyForce_X(-DASH_FORCE);
                    dashCooldownTimer = DASH_TIME;
                }
            }

            if (dashCooldownTimer > 0.0f)
            {
                dashCooldownTimer -= dt;
            }

            // std::cout << dashCooldownTimer << std::endl;
        }

        void EntityCollision(float dt, Collider* collider)
        {
            if(CollisionHandler::get_instance()->MapCollision_BottomTile(collider->GetBoxCollider()))
            {
                m_force.Y = 0;
                m_is_grounded = true;

                int bottom_tile = (m_position.Y + 72) / 32;
                m_position.Y = 32 * (bottom_tile - 2) - 7;
            }
            else
            {
                m_is_grounded = false;
            }

            /* if(CollisionHandler::get_instance()->MapCollision_RightTile(collider->GetBoxCollider()))
            {
                int right_tile = (m_position.X + 72) / 32;
                m_position.X = 32 * (right_tile - 2) - 7;

                if(EventHandler::get_instance()->get_key_down(SDL_SCANCODE_E))
                {
                    m_velocity.X = 0;
                }
            }

            if(CollisionHandler::get_instance()->MapCollision_LeftTile(collider->GetBoxCollider()))
            {
                int left_tile = m_position.X / 32;
                m_position.X = 32 * left_tile + 30;
            }

            if(CollisionHandler::get_instance()->MéapCollision_TopTile(collider->GetBoxCollider()))
            {

            } */
        }
};

#endif // RIGIDBODY_H
