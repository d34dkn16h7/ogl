#ifndef RENDERER_H
#define RENDERER_H

class Geometry;
class Program;

#include <GL/glew.h>
#include <GL/glfw.h>
#include <stdexcept>
#include <vector>

using namespace std;

class Gui;
class Camera;
class Program;
class Geometry;
class Renderer
{
private:
    static Camera *cam;
    static Program *prog;
    static vector<Geometry*> drawObjects;
    static vector<Gui*> drawGUI;
public:
    static bool Setup(int,int,int);
    static void Render();
    static void RenderObjects();
    static void RenderGUI();
    static void GenData();
    static void RegObject(Geometry*);
    static void UnRegObject(Geometry*);
    static void RegGUI(Gui*);
    static void UnRegGUI(Gui*);
};

#endif // RENDERER_H
