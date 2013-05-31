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
    vector<GameObject*> Intersect();
    ~Collider();

    static vector<GameObject*> GetAll(vec3);
    static GameObject* Get(vec3);
    static vector<GameObject*> Intersect( Collider* );
};

#endif // COLLIDER_H
