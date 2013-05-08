#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class Geometry;

#include <stdexcept>
#include "geometry.h"

using namespace std;

class GameObject : public Geometry
{
private:
    void LoadPrefab(string);
public:
    GameObject(string = "cube");
};

#endif // GAMEOBJECT_H
