#include "map.h"
#include "game.h"
#include "tools.h"
#include "gameObject.h"

Map* Map::ins; /// Current map instance

void Map::LoadMap(string fSrc) /// Load and construct gameObjects by .mp file
{
    ins = this;
    Tools::Token mapToken( Tools::File::LoadFile(fSrc) );
    GameObject *gmo = nullptr;
    data.clear();
    while( mapToken.Next() != "#endToken" )
    {
        if( Tools::Settings::isObject( mapToken.Current() )) /// Make object?
        {
            gmo = new GameObject(  mapToken.Current() );
            data.push_back( gmo );
        }
        else if(gmo != nullptr) /// Property if not empty object?
        {
            if(mapToken == "onControl" )
                Game::onControl = gmo;
            else if(mapToken == "pos" )
                gmo->transform.uPosition( mapToken.GetNVec3() );
            else if(mapToken == "rot" )
                gmo->transform.uRotation( mapToken.GetNVec3() );
            else if(mapToken == "scale" )
                gmo->transform.uScale( mapToken.GetNVec3() );
            else if(mapToken == "staticObject")
                gmo->DestroyComponents();
        }
    }
}

void Map::SaveMap(string tFile) /// Save map file
{
    std::stringstream mstr;
    for(GameObject* gmo : data)
    {
        vec3 tVec;
        vec4 tVec4;

        mstr << gmo->gPtr->idString << endl;
    /// Position
        tVec = gmo->transform.gPosition();
        Tools::Str::AddHashStreamVec3(mstr ,"pos" , tVec );
    /// Scale
        tVec = gmo->transform.gScale();
        if(tVec != vec3(1,1,1))
            Tools::Str::AddHashStreamVec3(mstr ,"scale" , tVec );
    /// Rotation
        tVec = gmo->transform.gRotation();
        if(tVec != vec3(0,0,0))
            Tools::Str::AddHashStreamVec3(mstr ,"rot" , tVec);

        if(gmo == Game::onControl)
            mstr << "\tonControl" << endl;
    }
    cout << "Map saved : " << tFile << "  :: Map Size : " << data.size() << endl;
    Tools::File::SaveFile(tFile,mstr.str());
}

void Map::Reg(GameObject* gmo) /// Register gameObject to map
{
    data.push_back(gmo);
}

void Map::UnReg(GameObject* gmo) /// Remove gameObject form map
{
    for(unsigned int i = 0 ; i < data.size();i++)
        if(gmo == data[i])
            data.erase(data.begin() + i);
}
