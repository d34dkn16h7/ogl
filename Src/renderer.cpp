#include <iostream>
#include "gui.h"
#include "game.h"
#include "camera.h"
#include "program.h"
#include "geometry.h"
#include "renderer.h"

Camera* Renderer::cam;
Program* Renderer::prog;
vector<Geometry*> Renderer::drawObjects;
vector<Gui*> Renderer::drawGUI;

void Renderer::Render()
{
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    RenderObjects();
    //RenderGUI();

    glfwSwapBuffers();
}
void Renderer::RenderObjects()
{
    int edges = 0;
    GLenum type = GL_TRIANGLES;
    string lastDrawName = "null";
    prog->SetUniform("cameraMatrix",cam->GetMatrix());
    for(Geometry* gmo : drawObjects)
    {
        if( Game::ins->editor.isSelected( (GameObject*)gmo ) )
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        else
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

        prog->SetUniform("modelMatrix",gmo->GetModelMatrix());
        prog->SetUniform("color",gmo->GetColor());
        prog->Use(true);
        if(lastDrawName != gmo->gPtr->idString)
        {
            glBindVertexArray(gmo->gPtr->GetVAO());
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,gmo->gPtr->GetEBO());
            edges = gmo->gPtr->GetEdges();
            type = gmo->gPtr->GetType();
            lastDrawName = gmo->gPtr->idString;
        }
        glDrawElements(type,edges,GL_UNSIGNED_INT,0);
    }

    prog->Use(false);
    glBindVertexArray(0);
}
void Renderer::RenderGUI()
{
    int edges = 0;
    GLenum type = GL_TRIANGLES;
    string lastDrawName = "null";

    Program::Use(true,"Gui");
    Program::GetProgramIns("Gui")->SetUniform("color", vec4(1,1,1,1));

    for(Gui* gObj : drawGUI)
    {
        Program::GetProgramIns("Gui")->SetUniform("scale", gObj->GetScale() );
        if(lastDrawName != gObj->master->idString)
        {
            glBindVertexArray(gObj->master->GetVAO());
            glBindBuffer(GL_ARRAY_BUFFER,gObj->master->GetVBO());
            edges = gObj->master->GetEdges();
            type = gObj->master->GetType();
            lastDrawName = gObj->master->idString;
        }
        glDrawArrays(type,0,edges);
    }
    Program::Use(false,"Gui");
    glBindVertexArray(0);
}
bool Renderer::Setup(int w,int h , int screenState)
{
    glfwInit();
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
    glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, GL_TRUE);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    if(!glfwOpenWindow(w, h, 8, 8, 8, 8, 16, 0, screenState) )
    {
        glfwOpenWindowHint(GLFW_OPENGL_PROFILE,0);
        if(!glfwOpenWindow(w, h, 8, 8, 8, 8, 16, 0, screenState))
        {
            cout << "glfwOpenWindow() Fail\n";
            return false;
        }
        cout << "GLFW_OPENGL_PROFILE -> 0\n";

    }
    glfwSetWindowTitle("openGL 3.2 -PRE.ALPHA");
    glfwSwapInterval(0);
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
        cout << "glewInit() Fail!\n";
        return false;
    }
    if(!GLEW_VERSION_3_2)
    {
        cout << "OpenGL 3.2 API is not available.\n";
        return false;
    }
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    cam = new Camera(w,h);
    prog = new Program("Data/Shaders/dVS.glsl","Data/Shaders/dFS.glsl","Model");//new Program("Data/Shaders/guiVS.glsl","Data/Shaders/guiFS.glsl","Gui");
    return true;
}
void Renderer::RegObject(Geometry *obj)
{
    drawObjects.push_back(obj);
}
void Renderer::UnRegObject(Geometry *obj)
{
    for(unsigned int i = 0;i < drawObjects.size();i++)
        if(drawObjects[i] == obj)
            drawObjects.erase(drawObjects.begin() + i);
}
void Renderer::RegGUI(Gui* obj)
{
    drawGUI.push_back(obj);
}
void Renderer::UnRegGUI(Gui* obj)
{
    for(unsigned int i = 0;i < drawGUI.size();i++)
        if(drawGUI[i] == obj)
            drawGUI.erase(drawGUI.begin() + i);
}
