#ifndef PHYSICS_H
#define PHYSICS_H

#include <glm/glm.hpp>
#include <vector>
#include "gameobject.h"
#include "component.h"

using namespace std;
using namespace glm;

class Physics : public Component
{
private:
    static vector<Physics*> physics;
    vec3 constForce;
public:
    Physics(GameObject*);
    virtual ~Physics();
    void Start();
    void Update();

    void Move(vec3);
    void AddForce(vec3);
    void AddConstantForce(vec3);

    static void Reg(Physics*);
    static void UnReg(Physics*);
    static void UpdateAll();
};

#endif // PHYSICS_H
