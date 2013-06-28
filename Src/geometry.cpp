#include "program.h"
#include "geometry.h"
#include "renderer.h"

vector< GData* > Geometry::gData;

void Geometry::Load(string fSrc)
{
    LoadSatus res = LoadData(fSrc);
    if(res != LoadSatus::Fail)
    {
        if(res != LoadSatus::AlreadyLoaded)
            LinkData();
    }
    else
        throw runtime_error("Can't load model file : " + fSrc);
}
GData* Geometry::Find(string sStr)
{
    for(GData* val : gData)
        if(val->idString == sStr)
            return val;

    return nullptr;
}
LoadSatus Geometry::LoadData(string fSrc)
{
    gPtr = Find(fSrc);
    if(gPtr == nullptr)
    {
        gPtr = new GData();
        gPtr->idString = nameToken;
        fstream file(fSrc.c_str());
        if(file.is_open())
        {
            GLfloat x,y,z;
            int f1,f2,f3;
            string type = "null type";
            while(!file.eof())
            {
                file >> type;
                if(type == "v")
                {
                    file >> x >> y >> z;
                    gPtr->verticles.push_back(x);
                    gPtr->verticles.push_back(y);
                    gPtr->verticles.push_back(z);
                }
                if(type == "c")
                {
                    file >> x >> y >> z;
                    gPtr->colorData.push_back(x);
                    gPtr->colorData.push_back(y);
                    gPtr->colorData.push_back(z);
                }
                if(type == "f")
                {
                    file >> f1 >> f2 >> f3;
                    f1 -= 1;f2 -= 1;f3 -= 1;
                    gPtr->elementary.push_back( (GLuint)f1 );
                    gPtr->elementary.push_back( (GLuint)f2 );
                    gPtr->elementary.push_back( (GLuint)f3 );
                }
            }
            gData.push_back(gPtr);
            return LoadSatus::Loaded;
        }
        else return LoadSatus::Fail;
    }
    return LoadSatus::AlreadyLoaded;
}
void Geometry::LoadTexture(string imgPath)
{
    if(gPtr != nullptr)
    {
        gPtr->texture = SOIL_load_OGL_texture(imgPath.c_str(),SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
        if (0 == gPtr->texture)
            cout << "SOIL loading error: " <<  SOIL_last_result() << endl;
    }
}
void Geometry::LinkData()
{
    glGenVertexArrays( 1, &gPtr->vao );
    glBindVertexArray( gPtr->vao );

    glGenBuffers( 1, &gPtr->vbo );
    glBindBuffer( GL_ARRAY_BUFFER , gPtr->vbo );
    glBufferData( GL_ARRAY_BUFFER ,
                  (gPtr->verticles.size() * sizeof(gPtr->verticles[0])),
                  &gPtr->verticles[0],GL_STATIC_DRAW);

    glGenBuffers(1,&gPtr->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gPtr->ebo);

    glBufferData( GL_ELEMENT_ARRAY_BUFFER ,
                  (gPtr->elementary.size() * sizeof(gPtr->elementary[0])),
                  &gPtr->elementary[0],GL_STATIC_DRAW);

    GLint posAttrib = glGetAttribLocation( Program::GetProgram("Model"), "vert" );
    glVertexAttribPointer( posAttrib, 3, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( posAttrib );
}

// GData
int GData::GetEdges() const {return elementary.size();}
GLuint GData::GetType() const {return type;}
GLuint GData::GetVBO() const {return vbo;}
GLuint GData::GetVAO() const {return vao;}
GLuint GData::GetEBO() const {return ebo;}
