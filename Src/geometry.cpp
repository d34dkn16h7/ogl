#include "geometry.h"
#include <iostream>

map<string,Geometry> Geometry::Data;
bool Geometry::Load(string fSrc)
{
    if(LoadData(fSrc) != eLoad::Fail)
    {
        LinkData();
        GenerateMatrix();
        Renderer::Reg(this);
        return true;
    }
    return false;
}
eLoad Geometry::LoadData(string fSrc)
{
    d = &Data[fSrc];
    if(!d->isLoaded)
    {
        fstream file(fSrc.c_str());
        if(file.is_open())
        {
            edges = 1;
            GLfloat x,y,z;
            string type = "null type";
            while(!file.eof())
            {
                file >> type;
                if(type == "v")
                {
                    file >> x >> y >> z;
                    d->data.push_back(x);
                    d->data.push_back(y);
                    d->data.push_back(z);
                    d->edges++;
                }
                if(type == "c")
                {
                    file >> x >> y >> z;
                    d->colorData.push_back(x);
                    d->colorData.push_back(y);
                    d->colorData.push_back(z);
                }
            }
            d->isLoaded = true;
            std::cout << fSrc << " : Loaded" << std::endl;
            return eLoad::Ok;
        }
        else return eLoad::Fail;
    }
    return eLoad::AlreadyLoaded;
}
void Geometry::LinkData()
{
    glGenVertexArrays( 1, &d->vao );
    glBindVertexArray( d->vao );

    glGenBuffers( 1, &d->vbo );
    glBindBuffer( GL_ARRAY_BUFFER , d->vbo );
    glBufferData( GL_ARRAY_BUFFER ,
                  (d->data.size() * sizeof(d->data)),
                  &d->data[0],GL_STATIC_DRAW);
    GLint posAttrib = glGetAttribLocation( Program::sGetProgram(), "vert" );
    glVertexAttribPointer( posAttrib, 3, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( posAttrib );
}
void Geometry::GenerateMatrix()
{
    modelMatrix = translate(mat4(),position);
    modelMatrix *= rotate(mat4(),rotation.x , vec3(0,1,0));
    modelMatrix *= rotate(mat4(),rotation.y , vec3(1,0,0));
    modelMatrix *= scale(mat4(1.0),vScale);
}
//GET
void Geometry::uPosition(vec3 val)
{position = val;GenerateMatrix();}

void Geometry::aPosition(vec3 val)
{position += val;GenerateMatrix();}

void Geometry::uRotate(vec3 val)
{rotation = val;GenerateMatrix();}

void Geometry::aRotate(vec3 val)
{rotation += val;GenerateMatrix();}

void Geometry::uScale(vec3 val)
{vScale = val;GenerateMatrix();}

void Geometry::uScale(float val)
{vScale = vec3(val,val,val);GenerateMatrix();}

void Geometry::aScale(vec3 val)
{vScale += val;GenerateMatrix();}

void Geometry::aScale(float val)
{vScale += vec3(val,val,val);GenerateMatrix();}

void Geometry::uColor(vec4 val)
{color = val;}
//GET
int Geometry::GetEdges()
{return edges;}

vec3 Geometry::GetPosition()
{return position;}

vec3 Geometry::GetScale()
{return vScale;}

vec4 Geometry::GetColor()
{return color;}

GLuint Geometry::GetType()
{return type;}

GLuint Geometry::GetVBO()
{return vbo;}

GLuint Geometry::GetVAO()
{return vao;}

mat4 Geometry::GetModelMatrix()
{return modelMatrix;}
