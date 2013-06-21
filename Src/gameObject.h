#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <stdexcept>
#include <typeinfo>
#include "tools.h"
#include "geometry.h"
#include "component.h"

using namespace std;

class Geometry;
class Physics;
class Component;
class GameObject : public Geometry
{
private:
    void LoadPrefab(string);
public:
    vector<Component*> components;
    bool isActive;

    GameObject(string = "cube");
    virtual ~GameObject();


    template <typename compType> void AddComponent()
    {
        components.push_back( new compType(this) );
    }
    template <typename compType> compType GetComponent()
    {
        for(auto c : components)
            if(c->GetType() == typeid(compType).hash_code() )
                return (compType)c;

        return nullptr;
    }
    void DestroyComponents();
};

#endif // GAMEOBJECT_H
