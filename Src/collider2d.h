#ifndef COLLIDER_H
#define COLLIDER_H

#include <glm/glm.hpp>
#include <vector>
#include "tools.h"
#include "component.h"

using namespace std;
using namespace glm;
using namespace Tools;

enum Side
{
    Front,Back,Top,Bottom,Left,Right,Both,None
};

class GameObject;
class Collider2d : public Component
{
private:
    static vector<Collider2d*> colliders;

    float GetSize();
    static float GetSize(Collider2d*);

    Rect mRect;
public:
    Side c1,c2;
    Rect rect;

    Collider2d(GameObject*);
    Collider2d(GameObject* , Rect);
    ~Collider2d();

    void Start() {}
    void Update() {}

    void sSize(Rect);
    void sOffset(vec3);

    static GameObject* Get(vec3);
    static vector<GameObject*> GetAll(vec3);

    bool isGrounded();
    vector<Collider2d*> GetGrounded();

    vector<Collider2d*> Intersect();
    vector<Collider2d*> Intersect( vec3 );
    static vector<Collider2d*> Intersect( Collider2d* );
    static vector<Collider2d*> Intersect( Collider2d* , vec3);
};

#endif // COLLIDER_H
