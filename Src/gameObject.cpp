#include "gameObject.h"
#include "renderer.h"
#include "collider.h"
#include "physics.h"
#include "map.h"
#include <iostream>


const static string DataDir = "Data/";
GameObject::GameObject(string pref) : isActive(true)
{
    nameToken = pref;
    LoadPrefab(pref);
    Renderer::RegObject(this);
}

GameObject::~GameObject()
{
    Map::ins->Pop(this);
    Renderer::UnRegObject(this);
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
            file >> input;
            if(input == "model")
            {
                file >> sVal;
                Load( DataDir + sVal);
            }
            else if(input == "texture")
            {
                file >> sVal;
                if(gPtr != nullptr && sVal != "null")
                    LoadTexture( DataDir + "Textures/" + sVal);
            }
            else if(input == "scale")
            {
                vec3 tPos;
                file >> tPos.x >> tPos.y >> tPos.z;
                transform.uScale(tPos);
            }
            else if(input == "position")
            {
                vec3 tPos;
                file >> tPos.x >> tPos.y >> tPos.z;
                transform.uPosition(tPos);
            }
            else if(input == "physics")
                AddComponent<Physics>();
        }
    }
    else
        throw runtime_error("Can't read prefab file");
}
void GameObject::DestroyComponents()
{
    for(Component* c : components)
        delete c;

    components.clear();
}
