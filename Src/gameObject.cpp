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
                components.push_back( new Physics(this) );
            }
            else if(input == "collider")
            {
                components.push_back( new Collider(this) );
            }
        }
    }
    else
        throw runtime_error("Can't read prefab file");
}
