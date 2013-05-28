#include "tools.h"
#include "program.h"

GLuint* Program::dProg;
Program::Program(string vShaderSrc,string fShaderSrc)
{
    isReady = CompileShader(vert,GL_VERTEX_SHADER,vShaderSrc) &&
              CompileShader(frag,GL_FRAGMENT_SHADER,fShaderSrc);
    if(isReady)
    {
        LinkProgram();
        dProg = &prog;
    }
    else
        throw runtime_error("Shader Compile Error");
}
void Program::SetUniform(const string& name,const mat4& matrix)
{
    Use(true);
    const GLchar* attName = name.c_str();
    GLint uniform = glGetUniformLocation(prog, attName);
    if(uniform == -1)
        throw runtime_error("Can't acces uniform");
    glUniformMatrix4fv(uniform, 1, false, value_ptr(matrix));
    Use(false);
}
void Program::SetUniform(const string& name,const vec4 val)
{
    Use(true);
    const GLchar* attName = name.c_str();
    GLint uniform = glGetUniformLocation(prog, attName);
    if(uniform == -1)
        throw runtime_error("Can't acces uniform");
    glUniform4f(uniform , val.r,val.g,val.b,val.a);
    Use(false);
}
void Program::LinkProgram()
{
    prog = glCreateProgram();
    glAttachShader( prog, vert);
    glAttachShader( prog, frag);
    glBindFragDataLocation( prog, 0, "outColor" );
    glLinkProgram(prog);
}
GLuint& Program::GetProgram()
{
    return prog;
}
GLuint& Program::sGetProgram()
{
    return (*dProg);
}
void Program::Use(bool val)
{
    if(val)
    {
        glUseProgram(prog);
    }
    else
        glUseProgram(0);
}
void Program::sUse(bool val)
{
    if(val)
    {
        glUseProgram( (*dProg) );
    }
    else
        glUseProgram(0);
}
GLuint Program::CompileShader(GLuint& trg,GLuint type,string shaderSrc)
{
    trg = glCreateShader(type);
    string source =  Tools::File::tLoadFile(shaderSrc);
    const char* src = source.c_str();
    glShaderSource(trg,1,&src,NULL);
    glCompileShader(trg);
    GLint status;
    glGetShaderiv(trg,GL_COMPILE_STATUS,&status);
    return status;
}
