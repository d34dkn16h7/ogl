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

    return val;
}
GameObject* Collider::Get(vec3 pos)
{
    if(!colliders.empty())
        return colliders.front()->owner;
}
