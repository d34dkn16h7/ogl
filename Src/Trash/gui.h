#ifndef GUI_H
#define GUI_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <string>
#include <vector>

using namespace std;
using namespace glm;

class GUIData
{
public:
    string idString;

    vector<GLfloat> verticles;
    vector<GLfloat> colorData;

    GLuint vbo,vao,type = GL_TRIANGLES;

    int GetEdges() const;
    GLuint GetVBO() const;
    GLuint GetVAO() const;
    GLuint GetType() const;
};

class Gui
{
private:
    static vector< GUIData* > gData;

    float rot;
    vec2 pos;
    vec2 scl;

    int guiLayer;
    mat4 matrix;

    GUIData* Find(string);
    void MakeButton();
    void LinkData();
    void GenerateMatrix();
public:
    Gui();

    GUIData* master;
    mat4 GetMatrix() const;
    vec2 GetScale();
};

#endif // GUI_H
