#include "collider.h"

vector<Collider*> Collider::colliders;

Collider::Collider(GameObject* gmo)
{
    type = ComponentType::C_Collider;
    owner = gmo;
    xMin = yMin = -1;
    xMax = yMax = 1;
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
    return ((c->xMax - c->xMin) * scale.x) * ((c->yMax - c->yMin) * scale.y);
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
    for(Collider* c : colliders)
    {
        vec3 opos = owner->GetPosition();
        vec3 oscl = owner->GetScale();
        float xma = opos.x + (xMax * oscl.x), xmi = opos.x + (xMin * oscl.x);
        float yma = opos.y + (yMax * oscl.y), ymi = opos.y + (yMin * oscl.y);

        opos = c->owner->GetPosition();
        oscl = c->owner->GetScale();
        float cxma = opos.x + (xMax * oscl.x), cxmi = opos.x + (xMin * oscl.x);
        float cyma = opos.y + (yMax * oscl.y), cymi = opos.y + (yMin * oscl.y);

        if( ymi > cymi && ymi < cyma )
            if( (xmi > cxmi && xmi < cxma) || (xma > cxmi && xma < cxma) )
                return true;
    }

    return false;
}
Collider* Collider::GetGrounded()
{
    for(Collider* c : colliders)
    {
        vec3 opos = owner->GetPosition();
        vec3 oscl = owner->GetScale();
        float xma = opos.x + (xMax * oscl.x), xmi = opos.x + (xMin * oscl.x);
        float yma = opos.y + (yMax * oscl.y), ymi = opos.y + (yMin * oscl.y);

        opos = c->owner->GetPosition();
        oscl = c->owner->GetScale();
        float cxma = opos.x + (xMax * oscl.x), cxmi = opos.x + (xMin * oscl.x);
        float cyma = opos.y + (yMax * oscl.y), cymi = opos.y + (yMin * oscl.y);

        if( ymi > cymi && ymi < cyma )
            if( (xmi > cxmi && xmi < cxma) || (xma > cxmi && xma < cxma) )
                return c;
    }

    return nullptr;
}
vector<GameObject*> Collider::Intersect()
{
    return Intersect(this);
}
vector<GameObject*> Collider::Intersect( Collider* target) // EMPTY
{
    vector<GameObject*> gList;

    for(Collider* gmo : colliders)
    {
        //Collider* bH = FindBiggerHorizontal(gmo , target);
        //Collider* bV = FindBiggerVertical(gmo , target);
        //if()

        //calc intersection
        if(true)
            gList.push_back(gmo->owner);
    }

    return gList;
}
/*Collider* Collider::FindBiggerVertical(Collider* c1,Collider* c2)
{
    float s1 = c1->owner->GetScale().y;
    float s2 = c2->owner->GetScale().y;
    return ((c1->xMax - c1->xMin) * s1) > ((c2->xMax - c2->xMin) * s2) ? c1 : c2;
}
Collider* Collider::FindBiggerHorizontal(Collider* c1,Collider* c2)
{
    float s1 = c1->owner->GetScale().y;
    float s2 = c2->owner->GetScale().y;
    return ((c1->yMax - c1->yMin) * s1) > ((c2->yMax - c2->yMin) * s2) ? c1 : c2;
}*/
