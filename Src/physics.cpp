#include <typeinfo>
#include "physics.h"
#include "collider.h"
#include "gameobject.h"

vector<Physics*> Physics::physics; /// List of registered objects

Physics::Physics(GameObject* own) :
    Component(typeid(this).hash_code() , own) , constForce( vec3(0,0,0) )
{
    GameObject::AddComponent<Collider>(owner);
    Reg(this);
    Start();
}

Physics::~Physics() /// Unregister from update list
{
    UnReg(this);
}

void Physics::Start()
{
    collider = owner->GetComponent<Collider*>();
}

void Physics::Move(vec3 val) /// Move by val if not colliding
{
    vec3 cPos = owner->transform.gPosition() + val;

    if(collider != nullptr)
    {
        if(collider->Intersect(cPos).size() == 0)
            owner->transform.uPosition(cPos);
    }
    else /// Don't have collider so just move*/
        owner->transform.uPosition(cPos);
}

void Physics::AddForce(vec3 val) /// Empty
{
}

void Physics::AddConstantForce(vec3 force) /// Add force to constForce
{
    constForce += force;
}

void Physics::Reg(Physics* val) /// Add this object to update vector
{
    physics.push_back(val);
}

void Physics::UnReg(Physics* val)/// Remove this object from update vector
{
    for(unsigned int i = 0;i < physics.size();i++)
        if(physics[i] == val)
            physics.erase(physics.begin() + i);
}

void Physics::Update() /// Update this object
{
    if(owner->isActive)
    {
        if(collider != nullptr)
            isGrounded = collider->isGrounded();
        if(constForce != vec3(0,0,0))
            Move(constForce);
    }
}

void Physics::UpdateAll() /// Send update to all registered objects
{
    for(Physics* p : physics)
        p->Update();
}

/*
else if(canPush)
        {
            bool canMove = true;
            bool grunded = false;

            for(Collider* c : col){
                Physics* p = c->owner->GetComponent<Physics*>();
                if(p->isConst)
                    {grunded = true;break;}
            }

            for(Collider* c : col)
            {
                Physics* p = c->owner->GetComponent<Physics*>();
                if( !p->isConst )
                {
                    vec3 isMoved = p->owner->GetPosition();
                    if(!grunded)
                        p->Move( val / div ); // shit

                    if(p->owner->GetPosition() != (isMoved + val)) // did it move if not you can't move too
                        canMove = false;
                }
                else
                    canMove = false;
            }
            if(canMove)
                owner->uPosition( owner->GetPosition() + (val / div) );
        }
*/
