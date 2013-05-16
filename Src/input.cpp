#include "input.h"

bool Input::mKeyState[ MOUSE_KEY_COUNT ];
bool Input::mKeyStateRelased[ MOUSE_KEY_COUNT ];
bool Input::mKeyStatePressed[ MOUSE_KEY_COUNT ];

int Input::mouseWDelta,Input::lastWPos;
vec2 Input::lastPos,Input::mouseDelta;


void Input::Init()
{
    mouseWDelta = 0;
    lastPos = MousePos();
    glfwSetKeyCallback(Input::Keyboard);
    glfwSetMouseButtonCallback(Input::MouseKeys);
}
void Input::Update()
{
    UpdateMouse();
}
void GLFWCALL Input::Keyboard(int key ,int action)
{
    //cout << key << " : " << action << endl;
}
void GLFWCALL Input::MouseKeys(int key ,int action)
{
    mKeyState[key] = mKeyStatePressed[key] = ( action == GLFW_PRESS );
    mKeyStateRelased[key] = ( action == GLFW_RELEASE );
}
void Input::UpdateMouse()
{
    mouseDelta = MousePos() - lastPos;
    lastPos = MousePos();

    mouseWDelta = glfwGetMouseWheel() - lastWPos;
    lastWPos = glfwGetMouseWheel();
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
