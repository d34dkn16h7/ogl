#ifndef INPUT_H
#define INPUT_H

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>

#include "renderer.h"

using namespace glm;

class Input
{
    static bool mKeyState[3];
    static bool mKeyStateRelased[3];
    static bool mKeyStatePressed[3];
    static void UpdateMouse();
    static vec2 lastPos;
    static int lastWPos;
public:
    static vec2 mouseDelta; // don't forget y;
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
