#include "Vegito.h"

#include "Camera.h"
#include "Collider.h"
#include "CollisionHandler.h"
#include "SoundsManager.h"

#include <iostream>

#include "ObjectFactory.h"

//Register<Vegito> vegitoRegister("Vegito");

#include "tinyxml.h"

Vegito::Vegito(Properties* props) : Player(props)
{
    m_is_jumping = true;
    m_is_grounded = false;


    m_animation = new SpiritAnimation(true);

    m_rigid_body = new RigidBody();

    m_collider = new Collider;
    m_collider->SetBuffer(0, 0, 0, 0);
    m_collider->SetBoxCollider(m_transform->X, m_transform->Y, 50, 72);

    m_rigid_body->SetState();

    SoundsManager::GetInstance()->LoadEffect("jump", "jump.wav");
}

void Vegito::draw()
{
    m_animation->Draw(m_transform->X, m_transform->Y, m_width, m_height, 1.0f, 1.0f);

    Vector2D cam = Camera::GetInstance()->GetPosition();
    SDL_Rect box = m_collider->GetBoxCollider();
    box.x -= cam.X;
    // box.y -= cam.Y;
    //SDL_RenderDrawRect(Engine::GetInstance()->GetRenderer(), &box);
}

void Vegito::update(float dt)
{
    m_rigid_body->UnsetForce();

    AnimationState();

    m_is_attacking = false;
    m_is_flying = false;

    if(Event::GetInstance()->GetKeyDown(SDL_SCANCODE_E))
    {
        m_is_flying = true;
        m_rigid_body->ApplyForce_X(MOVING_FORWARD * 2);
        //m_animation->SetAnimation("vegito_fly", 4, 255);
    }

    if(Event::GetInstance()->GetKeyDown(SDL_SCANCODE_Q))
    {
        m_is_flying = true;
        m_rigid_body->ApplyForce_X(MOVING_BACKWARD * 2);
        //m_animation->SetAnimation("vegito_fly", 4, 255, SDL_FLIP_HORIZONTAL);
    }

    if(Event::GetInstance()->GetKeyDown(SDL_SCANCODE_E) and Event::GetInstance()->GetKeyDown(SDL_SCANCODE_CAPSLOCK))
    {
       // m_rigid_body->ApplyForce_X(MOVING_FORWARD * MOVING_SPEED * 3);
        m_animation->SetSpiritAnimation("vegito_dash", 1, 2, 255, SDL_FLIP_NONE);
    }

    if(Event::GetInstance()->GetKeyDown(SDL_SCANCODE_Q) and Event::GetInstance()->GetKeyDown(SDL_SCANCODE_CAPSLOCK))
    {
        //m_rigid_body->ApplyForce_X(MOVING_BACKWARD * MOVING_SPEED * 3);
        m_animation->SetSpiritAnimation("vegito_dash", 1, 2, 255, SDL_FLIP_HORIZONTAL);
    }

    if(Event::GetInstance()->GetKeyDown(SDL_SCANCODE_A))
    {
        m_animation->SetSpiritAnimation("vegito_protects", 1, 1, 255, SDL_FLIP_NONE);
        //m_sequence_animation->SetCurrentSequence("vegito_guard");
        m_rigid_body->UnsetForce_X();
    }

    if(Event::GetInstance()->GetKeyDown(SDL_SCANCODE_L))
    {
        m_is_attacking = true;
        m_rigid_body->UnsetForce_X();
    }

    if(Event::GetInstance()->GetKeyDown(SDL_SCANCODE_SPACE))
    {
        m_animation->SetSpiritAnimation("vegito_jump", 1, 1, 100, SDL_FLIP_NONE);
        SoundsManager::GetInstance()->PlayEffect("jump");
    }

    m_animation->Update(dt);

    m_transform->X = m_rigid_body->GetPosition().X;
    m_transform->Y = m_rigid_body->GetPosition().Y;

    m_last_safe_position.X = m_transform->X;
    m_last_safe_position.Y = m_transform->Y;

    m_collider->SetBoxCollider(m_last_safe_position.X, m_last_safe_position.Y, 65, 72);
    m_collider->SetBuffer(-18, 0, 0, 0);

    m_rigid_body->UpdateCharacter(dt, m_collider, m_last_safe_position);

    m_origin->X = m_transform->X + m_width/2;
    // m_origin->Y = m_transform->Y + m_height/2;
}

void Vegito::AnimationState()
{
    m_animation->SetSpiritAnimation("vegito_stand", 1, 4, 255, SDL_FLIP_NONE);

    if(m_is_flying and Event::GetInstance()->GetAxis() == 1)
    {
        m_animation->SetSpiritAnimation("vegito_fly", 1, 4, 255, SDL_FLIP_NONE);
    }
    if(m_is_flying and Event::GetInstance()->GetAxis() == -1)
    {
        m_animation->SetSpiritAnimation("vegito_fly", 1, 4, 255, SDL_FLIP_HORIZONTAL);
    }

    if(m_is_attacking and Event::GetInstance()->GetAxis() == 1)
    {
        m_animation->SetSpiritAnimation("vegito_legs_attack", 1, 5, 100, SDL_FLIP_NONE);
    }
    if(m_is_attacking and Event::GetInstance()->GetAxis() == -1)
    {
        m_animation->SetSpiritAnimation("vegito_legs_attack", 1, 5, 100, SDL_FLIP_HORIZONTAL);
    }
}

void Vegito::clean()
{
    TextureManager::GetInstance()->Clean();
    delete m_rigid_body;
    delete m_collider;
}
