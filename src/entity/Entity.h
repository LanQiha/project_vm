#ifndef ENTITY_H
#define ENTITY_H

#include "GameObject.h"


class Entity : public GameObject
{
    public:
        Entity(Properties* props) : GameObject(props) {}

        virtual void draw() = 0;
        virtual void update(float dt) = 0;
        virtual void clean() = 0 ;

    protected:
        std::string m_name;
};

#endif // ENTITY_H
