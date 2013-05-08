#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include "renderer.h"
#include "program.h"

using namespace std;

enum class eLoad
{
    Ok,Fail,AlreadyLoaded
};

class Geometry
{
private:
    vector<GLfloat> data;
    vector<GLuint> element;
    vector<GLfloat> colorData;
    static map< string , Geometry > Data;
    int edges = 0;

    mat4 modelMatrix;
    GLuint vbo,vao,type = GL_TRIANGLES;

    vec3 position = vec3(0,0,0);
    vec3 rotation = vec3(0,0,0);
    vec3 vScale = vec3(1,1,1);
    vec4 color = vec4(1,1,1,1);

    void LinkData();
    void GenerateMatrix();
    eLoad LoadData(string);
    bool isLoaded = false;
public:
    string mName = "unnamed";

    Geometry *d = nullptr;
    bool Load(string);
    void uPosition(vec3);
    void aPosition(vec3);
    void uRotate(vec3);
    void aRotate(vec3);
    void uScale(vec3);
    void uScale(float);
    void aScale(vec3);
    void aScale(float);
    void uColor(vec4);

    const int GetEdges();
    const vec4 GetColor();
    const GLuint GetVBO();
    const GLuint GetVAO();
    const GLuint GetType();
    const mat4 GetModelMatrix();
};
#endif // GEOMETRY_H
