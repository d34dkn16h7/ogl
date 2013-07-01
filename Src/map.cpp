#include "map.h"
#include "game.h"
#include "tools.h"
#include "gameObject.h"

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
        tVec = gmo->transform.gPosition();
        Tools::Str::AddHashStreamVec3(mstr ,"pos" , tVec , 1);
    //Scale
        tVec = gmo->transform.gScale();
        if(tVec != vec3(1,1,1))
            Tools::Str::AddHashStreamVec3(mstr ,"scale" , tVec , 1);
    //Rotation
        tVec = gmo->transform.gRotation();
        if(tVec != vec3(0,0,0))
            Tools::Str::AddHashStreamVec3(mstr ,"rot" , tVec , 1);

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

    while( t.Next() != "#endToken" )
    {
        if(isObject( t.Current() )) /// Make object?
        {
            gmo = new GameObject(t.Current());
            data.push_back( (gmo) );
        }
        else if(gmo != nullptr) /// Property if not empty object?
        {
            if(t.Current() == "onControl" )
                Game::onControl = gmo;
            else if(t.Current() == "pos" )
                gmo->transform.uPosition( t.GetNVec3() );
            else if(t.Current() == "rot" )
                gmo->transform.uRotation( t.GetNVec3() );
            else if(t.Current() == "scale" )
                gmo->transform.uScale( t.GetNVec3() );

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
        if(gmo == data[i])
            data.erase(data.begin() + i);
}
