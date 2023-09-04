#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <string>
#include <map>
#include <functional>
#include <memory>

#include "GameObject.h"


class ObjectFactory
{
    public:
        static ObjectFactory* GetInstance(){return s_instance = (s_instance != nullptr)? s_instance : new ObjectFactory();}

        GameObject* CreateObject(std::string type, Properties* props);
        void RegisterType(std::string class_name, std::function<GameObject*(Properties* props)> type); // The name of the constructor of that class

    private:
        ObjectFactory(){}
        static ObjectFactory* s_instance;
        std::map <std::string, std::function<GameObject*(Properties* props)>> m_type_registry;
};

template<class type>
class Register
{
    public:
        Register(std::string class_name)
        {
            ObjectFactory* factory = ObjectFactory::GetInstance();
            factory->RegisterType(class_name, [](Properties* props) -> GameObject* { return new type(props); });
        }
};

#endif // OBJECTFACTORY_H

/* GameObject* CreateObject(string type)
{
    if(type == player)
    {
        return new Player();
    }
    if(type == ennemy)
    {
        return new Ennemy();
    }
} */ //easy way of doing a game object factory

// Then we have to add this line of code -> static Register<Vegito> Register("PLAYER"), in the cpp file of the class.
// This will allow us to register the object.
// For exemple a player or a boss...
