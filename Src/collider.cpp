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
        if( oPos.x > (pos.x - 1) && oPos.x < (pos.x + 1) )
            if( oPos.y > (pos.y - 1) && oPos.y < (pos.y + 1) )
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
