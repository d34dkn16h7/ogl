#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;
using namespace glm;
enum LoadSatus
{
    Loaded,Fail,AlreadyLoaded
};
class GData
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

class Geometry
{
private:
    static vector< GData* > gData;

    vec3 position = vec3(0,0,0);
    vec3 rotation = vec3(0,0,0);
    vec3 vScale = vec3(1,1,1);
    vec4 color = vec4(-1,0,0,1);

    mat4 modelMatrix;

    GData* Find(string);

    void LinkData();
    void GenerateMatrix();
    LoadSatus LoadData(string);
public:
    string nameToken;
    GData* gPtr = nullptr;

    virtual ~Geometry();

    void Load(string);
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
    vec3 GetPosition() const;
    vec3 GetRotation() const;
    vec3 GetScale() const;
    vec4 GetColor() const;
    mat4 GetModelMatrix() const;
};
#endif // GEOMETRY_H
