#ifndef COMPONENT_H
#define COMPONENT_H

#include "gameObject.h"
#include <vector>

using namespace std;

class GameObject;
class Component
{
public:
    GameObject* owner;

    virtual ~Component();

    virtual void Start() = 0;
    virtual void Update() = 0;

    static void DestroyAll( vector<Component*>& );
};

#endif // COMPONENT_H
