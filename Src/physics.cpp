#include "physics.h"
#include "collider.h"

vector<Physics*> Physics::physics;

Physics::Physics(GameObject* own) : constForce( vec3(0,0,0) ) , isConst(true)
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
    Collider* c = (Collider*)owner->GetComponent( ComponentType::C_Collider );
    isGrounded = c->isGrounded();
    Move(constForce);
}
void Physics::Move(vec3 val)
{
    vec3 cPos = owner->GetPosition();
    cPos += val;

    Collider* c = (Collider*)owner->GetComponent( ComponentType::C_Collider );
    if(c != nullptr)
    {
        vector<Collider*> col = c->Intersect(c,cPos);
        if( col.size() == 0)
        {
            owner->uPosition(cPos);
        }
        else
        {
            if(owner->nameToken != "player")
                return;

            bool canMove = true;
            for(Collider* c : col)
            {
                Physics* p = (Physics*)c->owner->GetComponent(ComponentType::C_Physics);
                if( !p->isConst )
                {
                    vec3 isMoved = p->owner->GetPosition();
                    p->Move( val );
                    if(p->owner->GetPosition() != (isMoved + val)) // did it move if not you can't move too
                        canMove = false;
                }
                else
                    canMove = false;
            }

            if(owner->nameToken != "player") // bug!!!!!!!!
                return;

            if(canMove)
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
/*if(!c->isGrounded())
            owner->uPosition(cPos);
        else // push all down! ... why?
        {
            vector<Collider*> col = c->GetGrounded();

            for(Collider* c : col)
            {
                Physics* p = (Physics*)c->owner->GetComponent(ComponentType::C_Physics);
                if( p->isConst ? false : (!p->isGrounded && !isGrounded) )
                {
                    p->Move( val );
                    owner->uPosition(cPos);
                }
            }
        }*/
