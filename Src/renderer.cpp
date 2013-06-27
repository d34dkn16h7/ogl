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
GLuint tex_2d;

void Renderer::Render() /// Call All Render Func's
{
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    RenderObjects();//RenderGUI();

    glfwSwapBuffers( window );
}

void Renderer::RenderObjects() /// Render All Objects
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
        //prog->SetUniform("color",gmo->GetColor());
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

bool Renderer::Setup(int w,int h) /// Setup GLFW - GLEW + Window + Shaders
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

    PrintRendererInfo();

    tex_2d = SOIL_load_OGL_texture("Data/Textures/wood.jpg",SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_INVERT_Y);
    if (0 == tex_2d)
        cout << "SOIL loading error: " <<  SOIL_last_result() << endl;

    glActiveTexture (GL_TEXTURE0); // activate the first slot
    glBindTexture (GL_TEXTURE_2D, tex_2d);

    return true;
}

void Renderer::PrintRendererInfo() /// Print Main Info
{
    int iOpenGLMajor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
    int iOpenGLMinor = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);
    int iOpenGLRevision = glfwGetWindowAttrib(window, GLFW_CONTEXT_REVISION);
    cout << "Status: GLFW Version " << glfwGetVersionString() << endl;
    cout << "Status: OpenGL Version: " << iOpenGLMajor << '.' << iOpenGLMinor << " Revision " << iOpenGLRevision << endl;
    cout << "Status: GLEW Version " << glewGetString(GLEW_VERSION) << endl;
}

void Renderer::RegObject(Geometry *obj) /// Register Geometry to Draw Vector
{
    drawObjects.push_back(obj);
}

void Renderer::UnRegObject(Geometry *obj) /// Remove Geometry from Draw Vector
{
    for(unsigned int i = 0;i < drawObjects.size();i++)
        if(drawObjects[i] == obj)
            drawObjects.erase(drawObjects.begin() + i);
}

GLFWwindow* Renderer::gWindow() /// Return GLFWwindow* handler
{
    return window;
}
