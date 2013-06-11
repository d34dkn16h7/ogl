#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>
#include "gameObject.h"

using namespace std;

enum ComponentType
{
    C_Physics,
    C_Collider
};

class GameObject;
class Component //Base Component
{
public:
    ComponentType type;
    GameObject* owner;

    virtual ~Component();

    virtual void Start() = 0;
    virtual void Update() = 0;

    // This looks like shit.
    static void AddComponent( vector<Component*>& , GameObject* , ComponentType);
    static Component* GetComponent( vector<Component*>& , ComponentType);
    static void DestroyAll( vector<Component*>& );
};

#endif // COMPONENT_H
