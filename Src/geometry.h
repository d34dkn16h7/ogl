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
    //vector<GLfloat> texture_cord;
    vector<GLfloat> verticles;
    vector<GLfloat> colorData;

    GLuint vbo,vao,ebo;
    GLuint texture = 0;
    GLuint type = GL_TRIANGLES;

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

    GData* Find(string);

    void LinkData();
    LoadSatus LoadData(string);
public:
    string nameToken;
    GData* gPtr = nullptr;

    void Load(string);
    void LoadTexture(string);
};
#endif // GEOMETRY_H
