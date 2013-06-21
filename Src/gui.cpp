#include "gui.h"
#include "program.h"
#include "renderer.h"
#include <iostream>

vector<GUIData*> Gui::gData;

Gui::Gui()
{
    master = Find("rect");
    if(master == nullptr)
    {
        MakeButton();
        LinkData();
    }
    GenerateMatrix();
    Renderer::RegGUI(this);
}
void Gui::MakeButton()
{
    master = new GUIData();

    master->verticles.push_back(-1);
    master->verticles.push_back(-1);

    master->verticles.push_back(-1);
    master->verticles.push_back(1);

    master->verticles.push_back(1);
    master->verticles.push_back(1);

    gData.push_back(master);
}
void Gui::LinkData()
{
    glGenVertexArrays( 1, &master->vao );
    glBindVertexArray( master->vao );

    glGenBuffers( 1, &master->vbo );
    glBindBuffer( GL_ARRAY_BUFFER , master->vbo );
    glBufferData( GL_ARRAY_BUFFER ,
                  (master->verticles.size() * sizeof(master->verticles[0])),
                  &master->verticles[0],GL_STATIC_DRAW);

    GLint posAttrib = glGetAttribLocation( Program::GetProgram("Gui"), "vert" );
    glVertexAttribPointer( posAttrib, 2, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( posAttrib );
}

GUIData* Gui::Find(string sStr)
{
    for(GUIData* val : gData)
        if(val->idString == sStr)
            return val;

    return nullptr;
}
mat4 Gui::GetMatrix() const {return matrix;}
vec2 Gui::GetScale()
{
    return vec2(.002f,.002f);
}
void Gui::GenerateMatrix()
{
}
// GUIData
int GUIData::GetEdges() const {return verticles.size();}
GLuint GUIData::GetType() const {return type;}
GLuint GUIData::GetVBO() const {return vbo;}
GLuint GUIData::GetVAO() const {return vao;}
