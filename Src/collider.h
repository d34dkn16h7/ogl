#ifndef COLLIDER_H
#define COLLIDER_H

#include <glm/glm.hpp>
#include <vector>
#include "gameObject.h"
#include "component.h"

using namespace std;
using namespace glm;

class Collider : public Component
{
private:
    static vector<Collider*> colliders;

    float GetSize();
    static float GetSize(Collider*);
    //static Collider* FindBiggerVertical(Collider*,Collider*);
    //static Collider* FindBiggerHorizontal(Collider*,Collider*);
public:
    float xMin,xMax,yMin,yMax;

    vec3 position;
    float width,height,depth;

    Collider(GameObject*);
    ~Collider();

    void Start() {}
    void Update() {}

    static GameObject* Get(vec3);
    static vector<GameObject*> GetAll(vec3);

    bool isGrounded();
    Collider* GetGrounded();

    vector<GameObject*> Intersect();
    static vector<GameObject*> Intersect( Collider* );
    static vector<GameObject*> Intersect( Collider* , vec3 );
};

#endif // COLLIDER_H
