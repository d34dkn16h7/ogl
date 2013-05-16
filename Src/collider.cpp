#include "collider.h"

vector<Collider*> Collider::colliders;

Collider::Collider(GameObject* gmo)
{
    owner = gmo;
    colliders.push_back(this);
}
Collider::~Collider()
{
    for(int i = 0;i < colliders.size();i++)
    {
        if(colliders[i] == this)
        {
            colliders.erase(colliders.begin() + i);
        }
    }
}
vector<GameObject*> Collider::GetAll(vec3 pos)
{
    vector<GameObject*> val;

    for(Collider* collider : colliders)
    {
        GameObject* gmo = collider->owner;
        vec3 oPos = gmo->GetPosition();
        float r = gmo->GetScale().x; // Works only cubic objects
        if( oPos.x > (pos.x - r) && oPos.x < (pos.x + r) )
            if( oPos.y > (pos.y - r) && oPos.y < (pos.y + r) )
            {
                val.push_back(gmo);
            }
    }

    return val;
}
GameObject* Collider::Get(vec3 pos)
{
    vector<GameObject*> val = GetAll(pos);
    if(!val.empty())
        return val.front();
    else
        return nullptr;
}
