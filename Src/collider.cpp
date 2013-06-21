#include <typeinfo>
#include "collider.h"
#include "gameObject.h"

vector<Collider*> Collider::colliders;

Collider::Collider(GameObject* own) : Collider(own , Rect(1,1) ) {}
Collider::Collider(GameObject* own , Rect r) : Component(typeid(this).hash_code() , own) , rect(r)
{
    if(owner->nameToken == "player") // shit
        rect = Rect(1,4);

    colliders.push_back(this);
}
Collider::~Collider()
{
    for(unsigned int i = 0; i < colliders.size(); i++)
        if(colliders[i] == this)
            colliders.erase(colliders.begin() + i);
}
float Collider::GetSize()
{
    return GetSize(this);
}
float Collider::GetSize(Collider* c)
{
    vec3 scale = c->owner->GetScale();
    return ((c->rect.xma - c->rect.xmi) * scale.x) * ((c->rect.yma - c->rect.ymi) * scale.y);
}
GameObject* Collider::Get(vec3 pos)
{
    vector<GameObject*> val = GetAll(pos);
    if(!val.empty())
        return val.front();
    else
        return nullptr;
}
vector<GameObject*> Collider::GetAll(vec3 pos)
{
    vector<GameObject*> val;
    for(Collider* c : colliders)
    {
        Rect r( c->rect );
        r.Scale( c->owner->GetScale() );
        r.AddOffset(pos);
        vec3 oPos = c->owner->GetPosition();

        if( oPos.x > r.xmi && oPos.x < r.xma )
            if( oPos.y > r.ymi && oPos.y < r.yma )
                val.push_back(c->owner);
    }

    return val;
}
bool Collider::isGrounded()
{
    return GetGrounded().size() == 0 ? false : true;
}
vector<Collider*> Collider::GetGrounded()
{
    vector<Collider*> val;
    Rect r(rect);
    r.Scale(owner->GetScale());
    r.AddOffset(owner->GetPosition());
    for(Collider* c : colliders)
    {
        Rect cr( c->rect);
        cr.Scale(c->owner->GetScale());
        cr.AddOffset(c->owner->GetPosition());

        if( (r.ymi > cr.ymi && r.ymi < cr.yma))
            if( (r.xmi > cr.xmi && r.xmi < cr.xma) || (r.xma > cr.xmi && r.xma < cr.xma) || (r.xma > cr.xma && r.xmi < cr.xmi) )
                val.push_back(c);
    }

    return val;
}
vector<Collider*> Collider::Intersect()
{
    return Intersect(this);
}
vector<Collider*> Collider::Intersect(vec3 nPos)
{
    return Intersect(this , nPos);
}
vector<Collider*> Collider::Intersect( Collider* target )
{
    return Intersect( target, target->owner->GetPosition() );
}
vector<Collider*> Collider::Intersect( Collider* target , vec3 uPos )
{
    vector<Collider*> val;
    Rect r(target->rect);
    r.Scale(target->owner->GetScale());
    r.AddOffset(uPos);
    for(Collider* c : colliders)
    {
        Rect cr( c->rect);
        cr.Scale(c->owner->GetScale());
        cr.AddOffset(c->owner->GetPosition());

        if( (r.ymi > cr.ymi && r.ymi < cr.yma) || (r.yma < cr.yma && r.yma > cr.ymi) || (r.yma > cr.yma && r.ymi < cr.ymi) )
            if( (r.xmi > cr.xmi && r.xmi < cr.xma) || (r.xma > cr.xmi && r.xma < cr.xma) || (r.xma > cr.xma && r.xmi < cr.xmi) )
                val.push_back(c);
    }

    return val;
}
