#include "physics.h"
#include "collider.h"

vector<Physics*> Physics::physics;

Physics::Physics(GameObject* own) : constForce( vec3(0,0,0) ) , isConst(true) , canPush(false)
{
    type = ComponentType::C_Physics;
    owner = own;

    if(owner->nameToken == "player")
        canPush = true;

    Reg(this);
}
Physics::~Physics()
{
    UnReg(this);
}
void Physics::Start() {}
void Physics::Update()
{
    if(owner->isActive)
    {
        Collider* c = (Collider*)owner->GetComponent( ComponentType::C_Collider );
        isGrounded = c->isGrounded();
        Move(constForce);
    }
}
void Physics::Move(vec3 val) // fucking shit
{
    vec3 cPos = owner->GetPosition();
    cPos += val;

    Collider* c = (Collider*)owner->GetComponent( ComponentType::C_Collider );
    if(c != nullptr)
    {
        vector<Collider*> col = c->Intersect(c,owner->GetPosition());
        if(col.size() != 0 && canPush)
        {
            owner->uPosition(cPos);
            return;
        }

        col = c->Intersect(c,cPos);
        if( col.size() == 0)
        {
            owner->uPosition(cPos);
        }
        else if(canPush)
        {
            bool canMove = true;
            bool grunded = false;

            for(Collider* c : col){
                Physics* p = (Physics*)c->owner->GetComponent(ComponentType::C_Physics);
                if(p->isConst)
                    {grunded = true;break;}
            }

            for(Collider* c : col)
            {
                Physics* p = (Physics*)c->owner->GetComponent(ComponentType::C_Physics);
                if( !p->isConst )
                {
                    vec3 isMoved = p->owner->GetPosition();
                    if(!grunded)
                        p->Move( val ); // shit

                    if(p->owner->GetPosition() != (isMoved + val)) // did it move if not you can't move too
                        canMove = false;
                }
                else
                    canMove = false;
            }
            if(canMove)
                owner->uPosition( owner->GetPosition() + val );
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
