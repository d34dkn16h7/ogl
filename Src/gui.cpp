#include "gui.h"
#include "program.h"
#include "renderer.h"
#include <iostream>

vector<GUIData*> Gui::gData;

Gui::Gui()
{
    std::cout << "new gui element \n";
    master = Find("rect");
    if(master == nullptr)
    {
        MakeData();
        LinkData();
    }
    Renderer::RegGUI(this);
}
void Gui::MakeData()
{
    master = new GUIData();

    master->verticles.push_back(-.1f);
    master->verticles.push_back(.1f);
    master->verticles.push_back(0);

    master->elementary.push_back(0);
    master->elementary.push_back(1);
    master->elementary.push_back(2);

    master->elementary.push_back(1);
    master->elementary.push_back(1);
    master->elementary.push_back(2);

    master->elementary.push_back(1);
    master->elementary.push_back(0);
    master->elementary.push_back(2);

    master->elementary.push_back(0);
    master->elementary.push_back(0);
    master->elementary.push_back(2);

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

    glGenBuffers(1,&master->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, master->ebo);

    glBufferData( GL_ELEMENT_ARRAY_BUFFER ,
                  (master->elementary.size() * sizeof(master->elementary[0])),
                  &master->elementary[0],GL_DYNAMIC_DRAW);

    GLint posAttrib = glGetAttribLocation( Program::sGetProgram(), "vert" );
    glVertexAttribPointer( posAttrib, 2, GL_FLOAT, GL_FALSE, 0, NULL );
    glEnableVertexAttribArray( posAttrib );
}

GUIData* Gui::Find(string sStr)
{
    for(GUIData* val : gData)
    {
        if(val->idString == sStr)
            return val;
    }

    return nullptr;
}
// GUIData
int GUIData::GetEdges() const {return elementary.size();}
GLuint GUIData::GetType() const {return type;}
GLuint GUIData::GetVBO() const {return vbo;}
GLuint GUIData::GetVAO() const {return vao;}
GLuint GUIData::GetEBO() const {return ebo;}
