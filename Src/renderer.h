#ifndef RENDERER_H
#define RENDERER_H

class Geometry;
class Program;

#include <GL/glew.h>
#include <GL/glfw.h>
#include <stdexcept>
#include <vector>
#include "program.h"
#include "camera.h"
#include "geometry.h"

using namespace std;

class Renderer
{
private:
    static Camera *cam;
    static Program *prog;
    static vector<Geometry*> drawList;
public:
    Renderer(Geometry *obj); // Alternative for static void Reg();
    static int win_w,win_h;
    static bool Setup(int,int,int);
    static void Render();
    static void GenData();
    static void Reg(Geometry*);
    static Camera* sCamera();
};

#endif // RENDERER_H
