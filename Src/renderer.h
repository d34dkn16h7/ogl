#ifndef RENDERER_H
#define RENDERER_H

class Geometry;
class Program;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>
#include <vector>

using namespace std;

class Gui;
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
    static vector<Gui*> drawGUI;
public:
    static bool Setup(int,int);
    static void printInfo();
    static void Render();

    static void RenderObjects();
    static void RenderGUI();
    static void GenData();

    static void RegObject(Geometry*);
    static void UnRegObject(Geometry*);

    static void RegGUI(Gui*);
    static void UnRegGUI(Gui*);

    static GLFWwindow* gWindow();
};

#endif // RENDERER_H
