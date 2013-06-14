#include "physics.h"
#include "collider.h"

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

    //else
    //    Move(constForce);
}
void Physics::Move(vec3 val)
{
    vec3 cPos = owner->GetPosition();
    cPos += val;

    Collider* c = (Collider*)owner->GetComponent( ComponentType::C_Collider );
    if(c != nullptr)
    {
        if(!c->isGrounded())
            owner->uPosition(cPos);
        else // push all down!
        {
            Physics* p = (Physics*)c->GetGrounded()->owner->GetComponent(ComponentType::C_Physics);
            //p->Move(constForce);
            p->Move(vec3(0,-.004f,0));
            owner->uPosition(cPos);
        }
    }
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
