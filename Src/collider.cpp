#include "collider.h"

vector<Collider*> Collider::colliders;

Collider::Collider(GameObject* gmo)
{
    owner = gmo;
    colliders.push_back(this);
}
vector<GameObject*> Collider::GetAll(vec3 pos)
{
    vector<GameObject*> val;

    return val;
}
GameObject* Collider::Get(vec3 pos)
{

    return nullptr;
}
