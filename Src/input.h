#ifndef INPUT_H
#define INPUT_H

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>

#define MOUSE_KEY_COUNT 3

using namespace glm;

class Input
{
    static vec2 lastPos;

    static bool mKeyState[MOUSE_KEY_COUNT];
    static bool mKeyStateRelased[MOUSE_KEY_COUNT];
    static bool mKeyStatePressed[MOUSE_KEY_COUNT];

    static int lastWPos;
    //func
    static void UpdateMouse();
    static void GLFWCALL Keyboard(int,int);
    static void GLFWCALL MouseKeys(int,int);
public:
    static vec2 mouseDelta;
    static int mouseWDelta;

    static void Init();
    static void Update();


    static bool isMouse(int);
    static bool isMousePressed(int);
    static bool isMouseRelased(int);
    static vec2 MousePos();
    static vec2 ScreenToWorld2d();
    static vec3 ScreenToWorld3d();
};

#endif // INPUT_H
