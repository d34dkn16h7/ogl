#include "map.h"
#include "gameObject.h"
#include <iostream>

const static string DataDir = "Data/";
GameObject::GameObject(string pref )
{
    LoadPrefab(pref);
    collider = new Collider(this);
}
GameObject::~GameObject()
{
    Map::ins->Pop(this);
    if(collider != nullptr)
        delete collider;
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
        }
    }
    else
        throw runtime_error("Can't read prefab file");
}
