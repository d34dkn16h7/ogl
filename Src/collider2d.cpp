#include <typeinfo>
#include "collider2d.h"
#include "gameObject.h"

vector<Collider2d*> Collider2d::colliders;

Collider2d::Collider2d(GameObject* own) :
    Collider2d(own , Rect(1,1) ) {}

Collider2d::Collider2d(GameObject* own , Rect r) :
    Component(typeid(this).hash_code() , own)
{
    mRect = rect = r;
    colliders.push_back(this);
}

Collider2d::~Collider2d()
{
    for(unsigned int i = 0; i < colliders.size(); i++)
        if(colliders[i] == this)
            colliders.erase(colliders.begin() + i);
}

void Collider2d::sSize(Rect r)
{
    mRect = rect = r;
}

void Collider2d::sOffset(vec3 offset)
{
    rect.AddOffset(offset);
}

float Collider2d::GetSize() /// Useless
{
    return GetSize(this);
}

float Collider2d::GetSize(Collider2d* c) /// Useless
{
    vec3 scale = c->owner->transform.gScale();
    return ((c->rect.xma - c->rect.xmi) * scale.x) * ((c->rect.yma - c->rect.ymi) * scale.y);
}

GameObject* Collider2d::Get(vec3 pos) /// GetAll.first()
{
    vector<GameObject*> val = GetAll(pos);
    if(!val.empty())
        return val.front();
    else
        return nullptr;
}

vector<GameObject*> Collider2d::GetAll(vec3 pos) /// Get all colliders who intesect with vec3
{
    vector<GameObject*> val;
    for(Collider2d* c : colliders)
    {
        Rect r( c->rect );
        r.Scale( c->owner->transform.gScale());
        r.AddOffset( c->owner->transform.gPosition());

        if( pos.x > r.xmi && pos.x < r.xma )
            if( pos.y > r.ymi && pos.y < r.yma )
                val.push_back(c->owner);
    }

    return val;
}

bool Collider2d::isGrounded() /// Is Grounded based on GetGrounded().size()
{
    return GetGrounded().size() == 0 ? false : true;
}

vector<Collider2d*> Collider2d::GetGrounded() /// Check if bottom bound is colliding
{
    vector<Collider2d*> val;
    Rect r(rect);
    r.Scale( owner->transform.gScale() );
    r.AddOffset(owner->transform.gPosition());
    for(Collider2d* c : colliders)
    {
        if(this == c) /// Stop colliding with yourself!
            continue;

        Rect cr( c->rect);
        cr.Scale(c->owner->transform.gScale());
        cr.AddOffset(c->owner->transform.gPosition());

        if( (r.ymi > cr.ymi && r.ymi < cr.yma))
            if( (r.xmi > cr.xmi && r.xmi < cr.xma) || (r.xma > cr.xmi && r.xma < cr.xma) || (r.xma > cr.xma && r.xmi < cr.xmi) )
                val.push_back(c);
    }

    return val;
}

vector<Collider2d*> Collider2d::Intersect() /// Wrapper to Intersect( Collider2d* )
{
    return Intersect(this);
}

vector<Collider2d*> Collider2d::Intersect( Collider2d* target ) /// Wrapper to Intersect( Collider2d* , vec3 )
{
    return Intersect( target, target->owner->transform.gPosition() );
}

vector<Collider2d*> Collider2d::Intersect(vec3 nPos) /// Wrapper to Intersect( Collider2d* , vec3 )
{
    return Intersect(this , nPos);
}

vector<Collider2d*> Collider2d::Intersect( Collider2d* target , vec3 uPos ) /// Intersect
{
    vector<Collider2d*> val;
    Rect r(target->rect);
    r.Scale(target->owner->transform.gScale());
    r.AddOffset(uPos);
    for(Collider2d* c : colliders)
    {
        if(target == c) /// Stop colliding with yourself!
            continue;

        Rect cr( c->rect);
        cr.Scale(c->owner->transform.gScale());
        cr.AddOffset(c->owner->transform.gPosition());


        if( (r.yma > cr.yma && r.ymi < cr.ymi) ) /// Both
        {
            if (r.xma > cr.xma && r.xmi < cr.xmi) /// Both
            {
                c->c1 = Side::Both;
                c->c2 = Side::Both;val.push_back(c);
            }
            else if( (r.xmi > cr.xmi && r.xmi < cr.xma) )/// Right
            {
                c->c1 = Side::Right;
                c->c2 = Side::Both;val.push_back(c);
            }
            else if(r.xma > cr.xmi && r.xma < cr.xma) /// Left
            {
                c->c1 = Side::Left;
                c->c2 = Side::Both;val.push_back(c);
            }
            else
            {
                c->c1 = Side::None;
                c->c2 = Side::None;
            }
        }
        else if( (r.ymi > cr.ymi && r.ymi < cr.yma) ) /// Top
        {
            if (r.xma > cr.xma && r.xmi < cr.xmi) /// Both
            {
                c->c1 = Side::Both;
                c->c2 = Side::Top;val.push_back(c);
            }
            else if( (r.xmi > cr.xmi && r.xmi < cr.xma)) /// Right
            {
                c->c1 = Side::Right;
                c->c2 = Side::Top;val.push_back(c);
            }
            else if(r.xma > cr.xmi && r.xma < cr.xma) /// Left
            {
                c->c1 = Side::Left;
                c->c2 = Side::Top;val.push_back(c);
            }
            else
            {
                c->c1 = Side::None;
                c->c2 = Side::None;
            }
        }
        else if( (r.yma < cr.yma && r.yma > cr.ymi) ) /// Bottom
        {
            if (r.xma > cr.xma && r.xmi < cr.xmi) /// Both
            {
                c->c1 = Side::Both;
                c->c2 = Side::Bottom;val.push_back(c);
            }
            else if( (r.xmi > cr.xmi && r.xmi < cr.xma)) /// Right
            {
                c->c1 = Side::Right;
                c->c2 = Side::Bottom;val.push_back(c);
            }
            else if(r.xma > cr.xmi && r.xma < cr.xma) /// Left
            {
                c->c1 = Side::Left;
                c->c2 = Side::Bottom;val.push_back(c);
            }
            else
            {
                c->c1 = Side::None;
                c->c2 = Side::None;
            }
        }

        /*if( (r.ymi > cr.ymi && r.ymi < cr.yma) || (r.yma < cr.yma && r.yma > cr.ymi) || (r.yma > cr.yma && r.ymi < cr.ymi) )
            if( (r.xmi > cr.xmi && r.xmi < cr.xma) || (r.xma > cr.xmi && r.xma < cr.xma) || (r.xma > cr.xma && r.xmi < cr.xmi) )
                val.push_back(c);*/
    }

    return val;
}
