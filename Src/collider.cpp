#include "collider.h"

vector<Collider*> Collider::colliders;

Collider::Collider(GameObject* gmo)
{
    owner = gmo;
    xMin = -1;xMax = 1;
    yMin = -1;yMax = 1;
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
        vec3 oScale = gmo->GetScale();
        float xMinGen = gmo->collider->xMin * oScale.x;
        float xMaxGen = gmo->collider->xMax * oScale.x;
        float yMinGen = gmo->collider->yMin * oScale.y;
        float yMaxGen = gmo->collider->yMax * oScale.y;
        if( oPos.x > (pos.x + xMinGen) && oPos.x < (pos.x + xMaxGen) )
            if( oPos.y > (pos.y + yMinGen) && oPos.y < (pos.y + yMaxGen) )
            {
                cout << "Selected -> " << gmo << endl;
                //cout << xMinGen << ":" << xMaxGen << endl;
                //cout << yMinGen << ":" << yMaxGen << endl;
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
