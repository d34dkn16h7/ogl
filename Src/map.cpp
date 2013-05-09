#include "map.h"
#include "game.h"
#include "tools.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <glm/glm.hpp>

using namespace glm;

void Map::LoadMap(string fSrc)
{
    string mstr = Tools::File::tLoadFile(fSrc);
    MakeMap(mstr);
}
void Map::SaveMap(string tFile)
{
    cout << "Map saved : " << tFile << endl;
    std::stringstream mstr;
    for(GameObject* gmo : data)
    {
        mstr << gmo->mName << endl;
        mstr << "\t" << "pos " << gmo->GetPosition().x << " " << gmo->GetPosition().y << " " <<  gmo->GetPosition().z << endl;
        if(gmo->GetScale() != vec3(1,1,1))
            mstr << "\t" << "scale " << gmo->GetScale().x << " " << gmo->GetScale().y << " " <<  gmo->GetScale().z << endl;

        mstr << "\t" << "col " << gmo->GetColor().x << " " << gmo->GetColor().y << " " <<  gmo->GetColor().z << " " << gmo->GetColor().w << endl;

        if(gmo == Game::onControl)
            mstr << "\t" << "player" << endl;
    }
    Tools::File::tSaveFile(tFile,mstr.str());
}
void Map::MakeMap(string strData)
{
    strData = Tools::Str::RemoveFormat(strData);
    Tools::Token t(strData);
    GameObject *gmo = nullptr;
    for(unsigned int i = 0;i < t.tokens.size() ;i++)
    {
        string token = t.tokens[i];

        //std::cout << "Current Token : " << token << std::endl;

        if(isObject(token))
        {
            gmo = new GameObject(token);
            data.push_back( (gmo) );
        }

        if(gmo != nullptr)
        {
            if(token == "player")
            {
                Game::onControl = gmo;
            }
            if(token == "pos")
            {
                float x,y,z;
                x = atof(t.tokens[i + 1].c_str());
                y = atof(t.tokens[i + 2].c_str());
                z = atof(t.tokens[i + 3].c_str());
                vec3 v(x,y,z);
                gmo->uPosition(v);
                i += 3;
            }
            if(token == "scale")
            {
                float x,y,z;
                x = atof(t.tokens[i + 1].c_str());
                y = atof(t.tokens[i + 2].c_str());
                z = atof(t.tokens[i + 3].c_str());
                vec3 v(x,y,z);
                gmo->uScale(v);
                i += 3;
            }
            if(token == "col")
            {
                float r,g,b,a;
                r = atof(t.tokens[i + 1].c_str());
                if (r != -1)
                {
                    g = atof(t.tokens[i + 2].c_str());
                    b = atof(t.tokens[i + 3].c_str());
                    a = atof(t.tokens[i + 4].c_str());
                    i += 4;
                }
                else
                {
                    g  = -1;
                    b = -1;
                    a = 1;
                    i += 1;
                }
                vec4 col(r,g,b,a);
                gmo->uColor(col);
            }
        }
    }
}
bool Map::isObject(string token)
{
    if(token == "cube")
        return true;
    if(token == "tris")
        return true;

    return false;
}
void Map::Put(GameObject* gmo)
{
    data.push_back(gmo);
}
