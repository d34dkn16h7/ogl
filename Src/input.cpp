#include "input.h"
#include "camera.h"
#include "renderer.h"

bool Input::mKeyState[ MOUSE_KEY_COUNT ];
bool Input::mKeyStateRelased[ MOUSE_KEY_COUNT ];
bool Input::mKeyStatePressed[ MOUSE_KEY_COUNT ];

vec2 Input::mouseWDelta,Input::lastPos,Input::mouseDelta,Input::mouseWheel,Input::lastMouseWheel;

void Input::Init()
{
    lastPos = MousePos();//glfwSetKeyCallback( Renderer::window , Input::Keyboard ); // No need for now.
    glfwSetMouseButtonCallback( Renderer::gWindow() , Input::MouseKeys );
    glfwSetScrollCallback( Renderer::gWindow() , Input::MouseScroll );
}
void Input::Update()
{
    UpdateMouse();
}
void Input::Keyboard(GLFWwindow* w, int key, int scancode, int action, int mods){}
void Input::MouseKeys(GLFWwindow* window, int key, int action, int mods)
{
    mKeyState[key] = mKeyStatePressed[key] = ( action == GLFW_PRESS );
    mKeyStateRelased[key] = ( action == GLFW_RELEASE );
}
void Input::MouseScroll(GLFWwindow* w,double x, double y)
{
    mouseWheel += vec2(x,y);
}

void Input::UpdateMouse()
{
    mouseDelta = MousePos() - lastPos;
    lastPos = MousePos();

    mouseWDelta = mouseWheel - lastMouseWheel;
    lastMouseWheel = mouseWheel;
}
bool Input::isMouse(int key)
{
    return mKeyState[key];
}
bool Input::isMousePressed(int key)
{
    bool val = mKeyStatePressed[key];
    mKeyStatePressed[key] = false;
    return val;
}
bool Input::isMouseRelased(int key)
{
    bool val = mKeyStateRelased[key];
    mKeyStateRelased[key] = false;
    return val;
}
bool Input::isKey(int key)
{
    return glfwGetKey(Renderer::gWindow(),key);
}
vec2 Input::MousePos()
{
    double x,y;
    glfwGetCursorPos(Renderer::gWindow() ,&x,&y);
    vec2 val = vec2(x,y);
    return val;
}
vec2 Input::ScreenToWorld2d()
{
    vec2 cpos = MousePos();
    bool xneg = false,yneg = false;
    int hX = Camera::MainCamera->ScreenSize.x / 2,hY = Camera::MainCamera->ScreenSize.y / 2;

    if(cpos.x > hX)
    {
        cpos.x -= hX;
        xneg = true;
    }
    if(cpos.y > hY)
    {
        cpos.y -= hY;
        yneg = true;
    }

    cpos.x = cpos.x / hX;
    cpos.y = cpos.y / hY;
    cpos.y = (1 - cpos.y);

    if(!xneg)
        cpos.x = (-1 + cpos.x);
    if(yneg)
        cpos.y = (-1 + cpos.y );

    return cpos;
}
vec3 Input::ScreenToWorld3d()
{
    float camZ = Camera::MainCamera->transform.gPosition().z;
    vec3 val = vec3(ScreenToWorld2d(),0);
    vec3 mult(camZ,camZ / Camera::MainCamera->GetAspectRatio(),0);
    val *= mult;
    glm::unProject(val, mat4(1.0) , Camera::MainCamera->GetPerspective(),vec4(-1,1,-1,1)); /// Need work!
    return val;
}
