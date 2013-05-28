#include "physics.h"

vector<Physics*> Physics::physics;

Physics::Physics(GameObject* own) : owner(own) , constForce( vec3(0,0,0) )
{
    physics.push_back(this);
}

void Physics::Move(vec3 val)
{
    vec3 cPos = owner->GetPosition();
    cPos += val;
    // is colliding? isGrounded?
    if(true)
        owner->uPosition(cPos);
    //else
        //invalid position
}
void Physics::AddForce(vec3 val) {}
void Physics::AddConstantForce(vec3 val)
{
    constForce += val;
}
void Physics::Update()
{
    Move(constForce);
}
void Physics::UpdateAll()
{
    for(Physics* p : physics)
    {
        p->Update();
    }
}
