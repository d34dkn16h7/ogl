#include <typeinfo>
#include "collider.h"
#include "gameObject.h"

vector<Collider*> Collider::colliders;

Collider::Collider(GameObject* own) : Component(typeid(this).hash_code() , own)
{
    xMin = yMin = -1;
    xMax = yMax = 1;

    if(owner->nameToken == "player") // shit
    {
        yMax = 4;
        yMin = -4;
    }

    colliders.push_back(this);
}
Collider::Collider(GameObject* own , Rect r) : Component(typeid(this).hash_code() , own) , box(r)
{
    if(owner->nameToken == "player") // shit
    {
        box = Rect(2,8);
    }

    colliders.push_back(this);
}
Collider::~Collider()
{
    for(unsigned int i = 0;i < colliders.size();i++)
    {
        if(colliders[i] == this)
        {
            colliders.erase(colliders.begin() + i);
        }
    }
}
float Collider::GetSize()
{
    return GetSize(this);
}
float Collider::GetSize(Collider* c)
{
    vec3 scale = c->owner->GetScale();
    return ((c->box.xma - c->box.xmi) * scale.x) * ((c->box.yma - c->box.ymi) * scale.y);
}
GameObject* Collider::Get(vec3 pos)
{
    vector<GameObject*> val = GetAll(pos);
    if(!val.empty())
    {
        return val.front();
    }

    else
        return nullptr;
}
vector<GameObject*> Collider::GetAll(vec3 pos)
{
    vector<GameObject*> val;
    for(Collider* collider : colliders)
    {
        vec3 oPos = collider->owner->GetPosition();
        vec3 oScale = collider->owner->GetScale();
        float xMinGen = collider->xMin * oScale.x;
        float xMaxGen = collider->xMax * oScale.x;
        float yMinGen = collider->yMin * oScale.y;
        float yMaxGen = collider->yMax * oScale.y;
        if( oPos.x > (pos.x + xMinGen) && oPos.x < (pos.x + xMaxGen) )
            if( oPos.y > (pos.y + yMinGen) && oPos.y < (pos.y + yMaxGen) )
            {
                val.push_back(collider->owner);
            }
    }

    return val;
}
bool Collider::isGrounded() // member func
{
    return GetGrounded().size() == 0 ? false : true;
}
vector<Collider*> Collider::GetGrounded()
{
    vector<Collider*> val;
    for(Collider* c : colliders)
    {
        vec3 opos = owner->GetPosition();
        vec3 oscl = owner->GetScale();
        float xma = opos.x + (xMax * oscl.x), xmi = opos.x + (xMin * oscl.x);
        float ymi = opos.y + (yMin * oscl.y);

        opos = c->owner->GetPosition();
        oscl = c->owner->GetScale();
        float cxma = opos.x + (c->xMax * oscl.x), cxmi = opos.x + (c->xMin * oscl.x);
        float cyma = opos.y + (c->yMax * oscl.y), cymi = opos.y + (c->yMin * oscl.y);

        if( ymi > cymi && ymi < cyma )
            if( (xmi > cxmi && xmi < cxma) || (xma > cxmi && xma < cxma) || (xma > cxma && xmi < cxmi) )
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
    for(Collider* c : colliders)
    {
        vec3 opos = uPos;
        vec3 oscl = target->owner->GetScale();

        float xma = opos.x + (target->xMax * oscl.x), xmi = opos.x + (target->xMin * oscl.x);
        float yma = opos.y + (target->yMax * oscl.y), ymi = opos.y + (target->yMin * oscl.y);

        opos = c->owner->GetPosition();
        oscl = c->owner->GetScale();

        float cxma = opos.x + (c->xMax * oscl.x), cxmi = opos.x + (c->xMin * oscl.x);
        float cyma = opos.y + (c->yMax * oscl.y), cymi = opos.y + (c->yMin * oscl.y);

        if( (ymi > cymi && ymi < cyma) || (yma < cyma && yma > cymi) || (yma > cyma && ymi < cymi) )
            if( (xmi > cxmi && xmi < cxma) || (xma > cxmi && xma < cxma) || (xma > cxma && xmi < cxmi) )
                val.push_back(c);
    }

    return val;
}
