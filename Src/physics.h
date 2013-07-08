#ifndef PHYSICS_H
#define PHYSICS_H

#include <glm/glm.hpp>
#include <vector>
#include "component.h"

using namespace std;
using namespace glm;

class Collider2d;
class GameObject;
class Physics : public Component
{
private:
    static vector<Physics*> physics; /// List of registered objects

    vec3 constForce; /// Const aplied force

    bool canPush; /// Can push?
    bool canBePushed; /// Can be pushed?
    bool isGrounded; /// Is grounded? Setted by collider in update
    Collider2d* collider; /// Local bounded collider
public:
    Physics(GameObject*);
    virtual ~Physics(); /// Call UnReg()
    void Start();

    void Move(vec3); /// Move by vec3 if not colliding
    void AddForce(vec3);
    void AddConstantForce(vec3);

    void Update(); /// Update this object
    static void UpdateAll(); /// Send update to all registered objects

    static void Reg(Physics*); /// Add this object to update vector
    static void UnReg(Physics*); /// Remove this object from update vector
};

#endif // PHYSICS_H
