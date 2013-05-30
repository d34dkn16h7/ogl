#ifndef GUI_H
#define GUI_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include <vector>

using namespace std;
using namespace glm;

typedef vec4 Rect;

class GUIData
{
public:
    string idString;

    vector<GLuint> elementary;
    vector<GLfloat> verticles;
    vector<GLfloat> colorData;

    GLuint vbo,vao,ebo,type = GL_TRIANGLES;

    int GetEdges() const;
    GLuint GetVBO() const;
    GLuint GetVAO() const;
    GLuint GetEBO() const;
    GLuint GetType() const;
};

class Gui
{
private:
    static vector< GUIData* > gData;

    Rect rect;
    int guiLayer;

    GUIData* Find(string);
    void MakeData();
    void LinkData();
public:
    Gui();

    GUIData* master;
};

#endif // GUI_H
