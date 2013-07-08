#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <fstream>
#include <vector>
#include <string>

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
    vector<GLfloat> textureCoord;
    vector<GLfloat> verticles;
    vector<GLfloat> colorData;

    GLuint vbo,vao,ebo;
    GLuint texture = 0;
    GLuint type = GL_TRIANGLES;

    void pVerticle(vec3);
    void pElement(GLuint);
    void pTextureCoord(vec2);

    int gEdges() const;
    GLuint gVBO() const;
    GLuint gVAO() const;
    GLuint gEBO() const;
    GLuint gType() const;
};

class Geometry
{
private:
    static vector< GData* > gData;

    GData* Find(string);

    void UniteData();
    void LinkData();
public:
    string fileToken;
    string nameToken;
    GData* gPtr = nullptr;

    void Load(string,string);
    void LoadTexture(string);
};
#endif // GEOMETRY_H
