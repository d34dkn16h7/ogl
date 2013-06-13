#include "map.h"
#include "game.h"
#include "tools.h"

Map* Map::ins;

void Map::LoadMap(string fSrc)
{
    ins = this;
    string mstr = Tools::File::tLoadFile(fSrc);
    MakeMap(mstr);
}
void Map::SaveMap(string tFile)
{
    cout << "Map saved : " << tFile << "  : Map Size -> " << data.size() << endl;
    std::stringstream mstr;
    for(GameObject* gmo : data)
    {
        vec3 tVec;
        vec4 tVec4;

        mstr << gmo->gPtr->idString << endl;
    //Position
        tVec = gmo->GetPosition();
        Tools::Str::AddHashStreamVec3(mstr ,"pos" , tVec , 1);
    //Scale
        tVec = gmo->GetScale();
        if(tVec != vec3(1,1,1))
            Tools::Str::AddHashStreamVec3(mstr ,"scale" , tVec , 1);
    //Rotation
        tVec = gmo->GetRotation();
        if(tVec != vec3(0,0,0))
            Tools::Str::AddHashStreamVec3(mstr ,"rot" , tVec , 1);
    //Color
        tVec4 = gmo->GetColor();
        if(tVec4 != vec4(-1,0,0,1)) //Null also default color for shader
            Tools::Str::AddHashStreamVec4(mstr ,"col" , tVec4 , 1);

        if(gmo == Game::onControl)
            mstr << "\tonControl" << endl;
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

        if(isObject(token))
        {
            gmo = new GameObject(token);
            data.push_back( (gmo) );
        }

        if(gmo != nullptr)
        {
            if(token == "onControl")
                Game::onControl = gmo;

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
                    g = b = 0;
                    a = 1;
                    i += 1;
                }
                vec4 col(r,g,b,a);
                gmo->uColor(col);
            }
        }
    }
}
bool Map::isObject(string token) //hard-coded vals? fuck no!
{
    if(token == "cube")
        return true;
    if(token == "tris")
        return true;
    if(token == "sphere")
        return true;
    if(token == "player")
        return true;

    return false;
}
void Map::Put(GameObject* gmo)
{
    data.push_back(gmo);
}
void Map::Pop(GameObject* gmo)
{
    for(unsigned int i = 0 ; i < data.size();i++)
    {

        if(gmo == data[i])
        {
            data.erase(data.begin() + i);
        }
    }
}
