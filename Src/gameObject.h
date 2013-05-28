#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include <stdexcept>
#include "geometry.h"
#include "collider.h"
#include "physics.h"

using namespace std;

class Geometry;
class Collider;
class Physics;
class GameObject : public Geometry
{
private:
    void LoadPrefab(string);
public:
    Physics* physics;
    Collider* collider;
    GameObject(string = "cube");
    virtual ~GameObject();
};

#endif // GAMEOBJECT_H
