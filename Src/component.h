#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>
#include "gameObject.h"
#include "tools.h"

using namespace std;



class GameObject;
class Component //Base Component
{
public:
    ComponentType type;
    GameObject* owner;

    virtual ~Component();

    virtual void Start() = 0;
    virtual void Update() = 0;
};

#endif // COMPONENT_H
