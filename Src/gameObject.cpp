#include "gameObject.h"
#include "renderer.h"
#include "collider.h"
#include "physics.h"
#include "tools.h"
#include "map.h"
#include <iostream>

const static string DataDir = "Data/";

GameObject::GameObject(string prefName) : isActive(true)
{
    nameToken = prefName;
    LoadPrefab();
    Renderer::RegObject(this);
}

GameObject::~GameObject()
{
    Map::ins->UnReg(this);
    Renderer::UnRegObject(this);
    DestroyComponents();
}

void GameObject::LoadPrefab() /// Load and make prefab by nameToken
{
    Tools::Token token( DataDir + nameToken + ".pref" , nameToken);

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
        else if(token.Current() == "csize")
        {
            vec3 tV = token.GetNVec3();
            Collider* c = GetComponent<Collider*>();
            if(c != nullptr)
                c->sSize(Rect(tV.x,tV.y));
        }
        else if(token.Current() == "coffset")
        {
            Collider* c = GetComponent<Collider*>();
            if(c != nullptr)
                c->sOffset(token.GetNVec3());
        }

    }
}

void GameObject::DestroyComponents() /// Delete all components
{
    for(Component* c : components)
        delete c;

    components.clear();
}
