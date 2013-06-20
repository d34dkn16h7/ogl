#ifndef PHYSICS_H
#define PHYSICS_H

#include <glm/glm.hpp>
#include <vector>
#include "component.h"

using namespace std;
using namespace glm;

class GameObject;
class Physics : public Component
{
private:
    static vector<Physics*> physics;
    vec3 constForce;

    bool canPush;
    bool isGrounded;
public:
    bool isConst;

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
