#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public GameObject
{
    public:
        Player(Properties* props) : GameObject(props) {}

        virtual void draw() = 0;
        virtual void update(float dt) = 0;
        virtual void clean() = 0 ;

    protected:
        std::string m_name;
};

#endif // PLAYER_H
