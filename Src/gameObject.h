#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include <stdexcept>
#include "geometry.h"
#include "component.h"
#include "tools.h"

using namespace std;

class Geometry;
class Component;
class GameObject : public Geometry
{
private:
    vector<Component*> components;
    void LoadPrefab(string);
public:
    GameObject(string = "cube");
    virtual ~GameObject();

    void AddComponent(ComponentType val);
    Component* GetComponent(ComponentType);
    void DestroyComponents();
};


#endif // GAMEOBJECT_H
