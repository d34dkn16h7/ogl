#include "input.h"

bool Input::mKeyState[3];
bool Input::mKeyStateRelased[3];
bool Input::mKeyStatePressed[3];

int Input::mouseWDelta,Input::lastWPos;
vec2 Input::lastPos,Input::mouseDelta;

void Input::Init()
{
    mouseWDelta = 0;
    lastPos = MousePos();
}
void Input::Update()
{
    UpdateMouse();
}
void Input::UpdateMouse()
{
    if(!mKeyState[0] && glfwGetMouseButton(0))
    {
        mKeyState[0] = true;
        mKeyStatePressed[0] = true;
    }
    else if(mKeyState[0] && !glfwGetMouseButton(0))
    {
        mKeyState[0] = false;
        mKeyStateRelased[0] = true;
    }

    if(!mKeyState[1] && glfwGetMouseButton(1))
    {
        mKeyState[1] = true;
        mKeyStatePressed[1] = true;
    }
    else if(mKeyState[1] && !glfwGetMouseButton(1))
    {
        mKeyState[1] = false;
        mKeyStateRelased[1] = true;
    }

    if(!mKeyState[2] && glfwGetMouseButton(2))
    {
        mKeyState[2] = true;
        mKeyStatePressed[2] = true;
    }
    else if(mKeyState[2] && !glfwGetMouseButton(2))
    {
        mKeyState[2] = false;
        mKeyStateRelased[2] = true;
    }

    mouseDelta = MousePos() - lastPos;
    lastPos = MousePos();

    mouseWDelta = glfwGetMouseWheel() - lastWPos;
    lastWPos = glfwGetMouseWheel();
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
bool Input::isMouse(int key)
{
    return mKeyState[key];
}
vec2 Input::MousePos()
{
    int x,y;
    glfwGetMousePos(&x,&y);
    vec2 val = vec2(x,y);
    return val;
}
vec2 Input::ScreenToWorld2d()
{
    vec2 cpos = MousePos();
    bool xneg = false,yneg = false;
    int hX = Renderer::win_w / 2,hY = Renderer::win_h / 2;

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
    float camZ = Camera::MainCamera->GetPosition().z;
    vec3 val = vec3(ScreenToWorld2d(),0);
    vec3 mult(camZ,camZ / Camera::MainCamera->GetAspectRatio(),0);
    val *= mult;
    glm::unProject(val, mat4(1.0) , Camera::MainCamera->GetPerspective(),vec4(-1,1,-1,1));
    return val;
}
