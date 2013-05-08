#include "map.h"
#include "game.h"
#include "tools.h"
#include <iostream>
#include <stdlib.h>
#include <glm/glm.hpp>

using namespace glm;

void Map::LoadMap(string fSrc)
{
    string mstr  = Tools::File::tLoadFile(fSrc);
    MakeMap(mstr);
}
void Map::MakeMap(string strData)
{
    strData = Tools::Str::RemoveFormat(strData);
    Tools::Token t(strData);
    GameObject *gmo = nullptr;
    for(unsigned int i = 0;i < t.tokens.size() ;i++)
    {
        string token = t.tokens[i];

        std::cout << "Current Token : " << token << std::endl;

        if(isObject(token))
        {
            gmo = new GameObject(token);
            data.push_back( (gmo) );
        }

        if(gmo != nullptr)
        {
            if(token == "player")
            {
                Game::ins->onControl = gmo;
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
            if(token == "rot")
            {
                float x,y,z;
                x = atof(t.tokens[i + 1].c_str());
                y = atof(t.tokens[i + 2].c_str());
                z = atof(t.tokens[i + 3].c_str());
                vec3 v(x,y,z);
                gmo->uRotate(v);
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
