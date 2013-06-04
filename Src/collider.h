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
    GameObject* owner;
    static vector<Collider*> colliders;

    static float GetSize(Collider*);
    static Collider* FindBiggerVertical(Collider*,Collider*);
    static Collider* FindBiggerHorizontal(Collider*,Collider*);
public:
    float xMin,xMax,yMin,yMax;

    Collider(GameObject*);
    ~Collider();

    static GameObject* Get(vec3);
    static vector<GameObject*> GetAll(vec3);

    vector<GameObject*> Intersect();
    static vector<GameObject*> Intersect( Collider* );
};

#endif // COLLIDER_H
