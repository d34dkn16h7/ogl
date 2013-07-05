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
    bool isTextureActive = false;
    Tools::Token token( DataDir + nameToken + ".pref" , nameToken);

    while(token.Next() != "#endToken")
    {
        if(token == "model")
            Load( DataDir + token.Next() , nameToken);

        if(token == "texture" && Tools::Settings::loadTextures)
        {
            if(gPtr != nullptr && token.Peek(1) != "null")
                LoadTexture( DataDir + "Textures/" + token.Next());
        }
        if(token == "physics")
            AddComponent<Physics>();

        if(token == "rot")
            transform.uRotation(token.GetNVec3());
        if(token == "scale")
            transform.uScale(token.GetNVec3());

        if(token == "csize")
        {
            vec3 tV = token.GetNVec3();
            Collider* c = GetComponent<Collider*>();
            if(c != nullptr)
                c->sSize(Rect(tV.x,tV.y));
        }
        if(token == "coffset")
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
