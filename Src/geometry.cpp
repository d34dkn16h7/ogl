#include "tools.h"
#include "program.h"
#include "geometry.h"
#include "renderer.h"

vector< GData* > Geometry::gData;

void Geometry::Load(string fSrc,string name) /// Load .obj model
{
    gPtr = Find(name);
    if(gPtr == nullptr)
    {
        gPtr = new GData();
        gPtr->idString = name;
        Tools::Token geoToken( Tools::File::LoadFile(fSrc) );

        while( geoToken.Next() !=  Tools::Token::EndToken )
        {
            if( geoToken == "v" )
                gPtr->pVerticle( geoToken.GetNVec3() );
            if(geoToken == "f")
                while( geoToken.CanGNum() )
                    gPtr->pElement( (GLuint)geoToken.GetNi() - 1 );
        }

        if(geoToken.tokens.size() > 2)
        {
            gData.push_back(gPtr);
            LinkData();
        }
        else
            cout << "Empty or corrupted model file : " << name <<  endl;
    }
}

GData* Geometry::Find(string sStr) /// Find a model ptr
{
    for(GData* val : gData)
        if(val->idString == sStr)
            return val;

    return nullptr;
}

void Geometry::LoadTexture(string imgPath) /// Laod and link texture
{
    if(gPtr != nullptr)
        if(gPtr->texture == 0)
        {
            if(Tools::Settings::TextureLoadModern)
            {
                gPtr->texture = SOIL_load_OGL_texture(imgPath.c_str(),SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
                if (0 == gPtr->texture)
                    cout << "SOIL loading error: " <<  SOIL_last_result() << endl;
            }
            else
            {

                glGenTextures( 1, &gPtr->texture );
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
                //glGenerateMipmap( GL_TEXTURE_2D );

                int width, height;
                unsigned char* image;

                glActiveTexture( GL_TEXTURE0 );
                glBindTexture( GL_TEXTURE_2D, gPtr->texture );
                image = SOIL_load_image( imgPath.c_str() , &width, &height, 0, SOIL_LOAD_RGB );
                glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,GL_UNSIGNED_BYTE, image );
                SOIL_free_image_data( image );
            }
        }
}

void Geometry::LinkData() /// Link VAO + VBO + EBO
{
    glGenVertexArrays( 1, &gPtr->vao );
    glBindVertexArray( gPtr->vao );

    glGenBuffers( 1, &gPtr->vbo );
    glBindBuffer( GL_ARRAY_BUFFER , gPtr->vbo );
    glBufferData( GL_ARRAY_BUFFER , (gPtr->verticles.size() * sizeof(gPtr->verticles[0])), &gPtr->verticles[0],GL_STATIC_DRAW);

    glGenBuffers(1,&gPtr->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gPtr->ebo);
    glBufferData( GL_ELEMENT_ARRAY_BUFFER , (gPtr->elementary.size() * sizeof(gPtr->elementary[0])), &gPtr->elementary[0],GL_STATIC_DRAW);

    GLuint vertAttrib = Program::GetProgramIns("Model")->gAttrib("vertex");

    glEnableVertexAttribArray( vertAttrib );
    glVertexAttribPointer( vertAttrib , 3, GL_FLOAT, GL_FALSE, 0, NULL );
}

// GData
void GData::pVerticle(vec3 vertex)
{
    verticles.push_back(vertex.x);
    verticles.push_back(vertex.y);
    verticles.push_back(vertex.z);
}

void GData::pElement(GLuint val)
{
    elementary.push_back ( val );
}

int GData::gEdges() const
{
    return elementary.size();
}

GLuint GData::gType() const
{
    return type;
}

GLuint GData::gVBO() const
{
    return vbo;
}

GLuint GData::gVAO() const
{
    return vao;
}

GLuint GData::gEBO() const
{
    return ebo;
}
