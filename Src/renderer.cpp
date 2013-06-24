#include "gui.h"
#include "game.h"
#include "editor.h"
#include "camera.h"
#include "program.h"
#include "geometry.h"
#include "renderer.h"

GLFWwindow* Renderer::window;
Camera* Renderer::cam;
Program* Renderer::prog;
vector<Geometry*> Renderer::drawObjects;
vector<Gui*> Renderer::drawGUI;

void Renderer::Render()
{
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    RenderObjects();//RenderGUI();

    glfwSwapBuffers( window );
}
void Renderer::RenderObjects()
{
    int edges = 0;
    GLenum type = GL_TRIANGLES;
    string lastDrawName = "null";
    prog->SetUniform("cameraMatrix",cam->GetMatrix());
    for(Geometry* gmo : drawObjects)
    {
        if( Game::ins->editor->isSelected( (GameObject*)gmo ) )
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
bool Renderer::Setup(int w,int h)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(w, h, "openGL 3.2 -PRE.ALPHA", 0, 0);
    if(!window)
    {
        glfwWindowHint(GLFW_OPENGL_PROFILE,0);
        window = glfwCreateWindow(w, h, "openGL 3.2 -PRE.ALPHA", 0, 0);
        if(!window)
        {
            cout << "glfwCreateWindow() Fail" << endl;
            return false;
        }
        cout << "GLFW_OPENGL_PROFILE -> 0" << endl;
    }
    glfwMakeContextCurrent(window);
    printInfo();
    glewExperimental = GL_TRUE;
    GLenum glewStatus = glewInit();
    if (glewStatus != GLEW_OK)
    {
        cout << "GLEW Error : " << glewGetErrorString(glewStatus) << endl;
        return false;
    }
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    cam = new Camera(w,h);
    prog = new Program("Data/Shaders/dVS.glsl","Data/Shaders/dFS.glsl","Model");
    return true;
}
void Renderer::printInfo()
{
    int iOpenGLMajor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
    int iOpenGLMinor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);
    int iOpenGLRevision = glfwGetWindowAttrib(window, GLFW_CONTEXT_REVISION);
    cout << "Status: GLFW Version " << glfwGetVersionString() << endl;
    cout << "Status: OpenGL Version: " << iOpenGLMajor << '.' << iOpenGLMinor << " Revision " << iOpenGLRevision << endl;
    cout << "Status: GLEW Version " << glewGetString(GLEW_VERSION) << endl;
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
GLFWwindow* Renderer::gWindow()
{
    return window;
}
