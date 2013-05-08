#ifndef INPUT_H
#define INPUT_H

#include <GL/glfw.h>
#include <glm/glm.hpp>

using namespace glm;

class Input
{
    static bool mKeyState[3];
    static bool mKeyStateRelased[3];
    static bool mKeyStatePressed[3];
    static void UpdateMouse();
    static vec2 lastPos;
public:
    static vec2 mouseDelta; // don't forget y;

    static void Init();
    static void Update();

    static bool isMouse(int);
    static bool isMousePressed(int);
    static bool isMouseRelased(int);
    static vec2 MousePos();
};

#endif // INPUT_H
