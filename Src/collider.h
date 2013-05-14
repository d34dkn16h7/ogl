#ifndef COLLIDER_H
#define COLLIDER_H

#include <glm/glm.hpp>
#include <vector>
#include "gameObject.h"

using namespace std;
using namespace glm;

class GameObject;
class Collider
{
private:
    static vector<Collider*> colliders;
    GameObject* owner;
public:
    float xMin,xMax,yMin,yMax;
    Collider(GameObject*);
    ~Collider();

    static vector<GameObject*> GetAll(vec3);
    static GameObject* Get(vec3);
};

#endif // COLLIDER_H
