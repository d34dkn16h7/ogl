#include "gameObject.h"
#include "collider.h"
#include "physics.h"
#include "map.h"
#include <iostream>

    /*//shitty desing.
    Physics* tPhysics = (Physics*)Component::GetComponent(components,ComponentType::C_Physics);
    if(tPhysics != nullptr)
        tPhysics->AddConstantForce(vec3(0,-.0001f,0));*/

const static string DataDir = "Data/";
GameObject::GameObject(string pref) : isActive(true)
{
    nameToken = pref;
    LoadPrefab(pref);
}
GameObject::~GameObject()
{
    Map::ins->Pop(this);
    DestroyComponents();
}
void GameObject::LoadPrefab(string fName)
{
    string fScr = DataDir + fName + ".pref";
    fstream file(fScr.c_str());
    if(file.is_open())
    {
        while(!file.eof())
        {
            string input,sVal;
            float fVal;
            file >> input;
            if(input == "model")
            {
                file >> sVal;
                Load( DataDir + sVal);
            }
            else if(input == "scale")
            {
                file >> fVal;
                uScale(fVal);
            }
            else if(input == "position")
            {
                vec3 tPos;
                file >> tPos.x >> tPos.y >> tPos.z;
                uPosition(tPos);
            }
            else if(input == "physics")
                AddComponent(ComponentType::C_Physics);
            else if(input == "collider")
                AddComponent(ComponentType::C_Collider);
        }
    }
    else
        throw runtime_error("Can't read prefab file");
}
Component* GameObject::GetComponent(ComponentType val)
{
        for(Component* c : components)
            if(c->type == val )
                return c;

        return nullptr;
}
void GameObject::AddComponent(ComponentType val)
{
    switch (val)
    {
    case ComponentType::C_Collider:
        components.push_back( new Collider(this) );
        break;
    case ComponentType::C_Physics:
        components.push_back( new Physics(this) );
        break;
    }
}
void GameObject::DestroyComponents()
{
    for(Component* c : components)
        delete c;

    components.clear();
}
