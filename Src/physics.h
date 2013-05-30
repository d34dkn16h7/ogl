#ifndef PHYSICS_H
#define PHYSICS_H

#include <glm/glm.hpp>
#include <vector>
#include "gameobject.h"

using namespace std;
using namespace glm;

class GameObject;
class Physics
{
private:
    static vector<Physics*> physics;

    GameObject* owner;

    vec3 constForce;
public:
    Physics(GameObject*);
    ~Physics();
    void Update();

    void Move(vec3);
    void AddForce(vec3);
    void AddConstantForce(vec3);

    static void Reg(Physics*);
    static void UnReg(Physics*);
    static void UpdateAll();
};

#endif // PHYSICS_H
