#include "component.h"

Component::~Component() {}
void Component::DestroyAll(vector<Component*> &m_components)
{
    for(Component* c : m_components)
        delete c;

    m_components.clear();
}
