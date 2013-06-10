#include "component.h"
#include "collider.h"
#include "physics.h"

void Component::AddComponent(vector<Component*> &m_components,GameObject* own,ComponentType val)
{
    switch (val)
    {
    case ComponentType::C_Collider:
        m_components.push_back( new Collider(own) );
        break;
    case ComponentType::C_Physics:
        m_components.push_back( new Physics(own) );
        break;
    }
}
Component* Component::GetComponent(vector<Component*> &m_components,ComponentType val)
{
    for(Component* c : m_components)
        if(c->type == val )
            return c;

    return nullptr;
}

Component::~Component() {}
void Component::DestroyAll(vector<Component*> &m_components)
{
    for(Component* c : m_components)
        delete c;

    m_components.clear();
}
