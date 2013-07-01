#include "gameObject.h"
#include "renderer.h"
#include "collider.h"
#include "physics.h"
#include "prefab.h"
#include "tools.h"
#include "map.h"
#include <iostream>

const static string DataDir = "Data/";

GameObject::GameObject(string pref) : isActive(true)
{
    nameToken = pref;
    LoadPrefab();
    Renderer::RegObject(this);
}

GameObject::~GameObject()
{
    Map::ins->Pop(this);
    Renderer::UnRegObject(this);
    DestroyComponents();
}

void GameObject::LoadPrefab() /// Load prefab by nameToken
{
    Tools::Token token( Tools::File::tLoadFile(DataDir + nameToken + ".pref") );

    while(token.Next() != "#endToken")
    {
        if(token.Current() == "model")
            Load( DataDir + token.Next() , nameToken);
        else if(token.Current() == "texture")
        {
            if(gPtr != nullptr && token.Peek(1) != "null")
                LoadTexture( DataDir + "Textures/" + token.Next());

        }
        else if(token.Current() == "physics")
            AddComponent<Physics>();
        else if(token.Current() == "scale")
                transform.uScale(token.GetNVec3());
    }
}

void GameObject::DestroyComponents() /// Delete all components
{
    for(Component* c : components)
        delete c;

    components.clear();
}
