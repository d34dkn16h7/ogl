#include "physics.h"

vector<Physics*> Physics::physics;

Physics::Physics(GameObject* own) : constForce( vec3(0,0,0) )
{
    type = ComponentType::C_Physics;
    owner = own;
    Reg(this);
}
Physics::~Physics()
{
    UnReg(this);
}
void Physics::Start() {}
void Physics::Update()
{
    Move(constForce);
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
void Physics::Reg(Physics* val)
{
    physics.push_back(val);
}
void Physics::UnReg(Physics* val)
{
    for(unsigned int i = 0;i < physics.size();i++)
    {
        if(physics[i] == val)
        {
            physics.erase(physics.begin() + i);
        }
    }
}
void Physics::UpdateAll()
{
    for(Physics* p : physics)
    {
        p->Update();
    }
}
