#ifndef RENDERER_H
#define RENDERER_H

class Geometry;
class Program;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <stdexcept>
#include <iostream>
#include <vector>

using namespace std;

class Camera;
class Program;
class Geometry;
class Renderer
{
private:
    static GLFWwindow* window;
    static Camera *cam;
    static Program *prog;
    static vector<Geometry*> drawObjects;
public:
    static bool Setup(int,int);
    static void PrintRendererInfo();

    static void Render();
    static void RenderObjects();

    static void RegObject(Geometry*);
    static void UnRegObject(Geometry*);

    static GLFWwindow* gWindow();
};

#endif // RENDERER_H
