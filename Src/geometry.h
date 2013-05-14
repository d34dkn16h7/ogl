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
    vector<GLfloat> colorData;
    static map< string , Geometry* > Data;
    int edges = 0;

    bool isLoaded = false;

    mat4 modelMatrix;
    GLuint vbo,vao,ebo,type = GL_TRIANGLES;

    vec3 position = vec3(0,0,0);
    vec3 rotation = vec3(0,0,0);
    vec3 vScale = vec3(1,1,1);
    vec4 color = vec4(1,1,1,1);

    void LinkData();
    void GenerateMatrix();
    eLoad LoadData(string);
public:
    virtual ~Geometry();
    vector<GLuint> element;
    string mName = "unnamed";

    Geometry *d = nullptr;
    bool Load(string);
    //SET
    void uPosition(vec3);
    void aPosition(vec3);
    void uRotate(vec3);
    void aRotate(vec3);
    void uScale(vec3);
    void uScale(float);
    void aScale(vec3);
    void aScale(float);
    void uColor(vec4);

    //GET
    int GetEdges();
    vec3 GetPosition();
    vec3 GetRotation();
    vec3 GetScale();
    vec4 GetColor();
    GLuint GetVBO();
    GLuint GetVAO();
    GLuint GetEBO();
    GLuint GetType();
    mat4 GetModelMatrix();
};
#endif // GEOMETRY_H
