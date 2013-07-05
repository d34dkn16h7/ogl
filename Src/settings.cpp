#include "tools.h"

using namespace Tools;

bool Settings::loadTextures;
bool Settings::TextureLoadModern = false;
string Settings::vertexShaderFileName;
string Settings::fragmentShaderFileName;
vector<string> Settings::objectNames;

void Settings::LoadSettings()
{
    Token setting( File::LoadFile("Data/settings") );
    while(setting.Next() != "#endToken")
    {
        if( setting == "#textureMode" )
            loadTextures = setting.Next() == "true" ? true : false;

        if( setting == "#textureModern" )
            TextureLoadModern = setting.Next() == "true" ? true : false;

        if( setting == "vertex" )
            vertexShaderFileName = setting.Next();

        if( setting == "fragment" )
            fragmentShaderFileName = setting.Next();
        if( setting == "#obj" )
            objectNames.push_back(setting.Next());
    }

}
