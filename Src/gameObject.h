#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


#include <stdexcept>
#include "geometry.h"
#include "collider.h"

using namespace std;

class Geometry;
class Collider;
class GameObject : public Geometry
{
private:
    Collider* collider;
    void LoadPrefab(string);
public:
    GameObject(string = "cube");
    virtual ~GameObject();
};

#endif // GAMEOBJECT_H
