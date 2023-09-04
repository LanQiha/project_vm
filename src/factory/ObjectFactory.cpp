#include "ObjectFactory.h"

ObjectFactory* ObjectFactory::s_instance = nullptr;

void ObjectFactory::RegisterType(std::string class_name, std::function<GameObject*(Properties* props)> type)
{
    m_type_registry[class_name] = type;
}

GameObject* ObjectFactory::CreateObject(std::string type, Properties* props)
{
    GameObject* object = nullptr;

    auto it = m_type_registry.find(type);

    if(it != m_type_registry.end())
        object = it->second(props);

    return object;
}
