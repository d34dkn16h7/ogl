#include "gameObject.h"
#include "collider.h"
#include "physics.h"
#include "map.h"
#include <iostream>

const static string DataDir = "Data/";
GameObject::GameObject(string pref)
{
    nameToken = pref;
    LoadPrefab(pref);

    /*//shitty desing.
    Physics* tPhysics = (Physics*)Component::GetComponent(components,ComponentType::C_Physics);
    if(tPhysics != nullptr)
        tPhysics->AddConstantForce(vec3(0,-.0001f,0));*/
}
GameObject::~GameObject()
{
    Map::ins->Pop(this);
    Component::DestroyAll( components );
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
            {
                Component::AddComponent(components,this,ComponentType::C_Physics);
            }
            else if(input == "collider")
            {
                Component::AddComponent(components,this,ComponentType::C_Collider);
            }
        }
    }
    else
        throw runtime_error("Can't read prefab file");
}
