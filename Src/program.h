#ifndef PROGRAM_H
#define PROGRAM_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <stdexcept>
#include <fstream>
#include <string>
#include <vector>
#include "tools.h"

using namespace std;
using namespace glm;

class Program
{
private:
    bool isReady;
    GLuint prog,vert,frag;
    static GLuint *dProg;
    GLuint CompileShader(GLuint& trg,GLuint type,string shaderSrc);
    void LinkProgram();
public:
    Program(string vShaderSrc = "Data/Shaders/def.vs",string fShaderSrc = "Data/Shaders/def.fs");
    void Use(bool);
    GLuint& GetProgram();
    void SetUniform(const string&,const mat4&);
    void SetUniform(const string&,const vec4);
    static void sUse(bool);
    static GLuint& sGetProgram();
};
#endif // PROGRAM_H
