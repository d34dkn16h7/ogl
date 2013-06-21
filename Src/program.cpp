#include "tools.h"
#include "program.h"

GLuint* Program::dProg;
vector<Program*> Program::programs;

Program::Program(string vShaderSrc ,string fShaderSrc ,string progName)
{
    name = progName;
    isReady = CompileShader(vert,GL_VERTEX_SHADER,vShaderSrc) &&
              CompileShader(frag,GL_FRAGMENT_SHADER,fShaderSrc);
    if(isReady)
    {
        LinkProgram();
        dProg = &prog;
        programs.push_back(this);
    }
    else
        throw runtime_error("Shader Compile Error");
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
void Program::LinkProgram()
{
    prog = glCreateProgram();
    glAttachShader( prog, vert);
    glAttachShader( prog, frag);
    glBindFragDataLocation( prog, 0, "outColor" );
    glLinkProgram(prog);
}
void Program::SetUniform(const string& name,const vec2& val)
{
    Use(true);
    const GLchar* attName = name.c_str();
    GLint uniform = glGetUniformLocation(prog, attName);
    if(uniform == -1)
        throw runtime_error("Can't acces uniform");
    glUniform2f(uniform , val.x,val.y);
    Use(false);
}
void Program::SetUniform(const string& name,const vec3& val)
{
    Use(true);
    const GLchar* attName = name.c_str();
    GLint uniform = glGetUniformLocation(prog, attName);
    if(uniform == -1)
        throw runtime_error("Can't acces uniform");
    glUniform3f(uniform , val.x,val.y,val.z);
    Use(false);
}
void Program::SetUniform(const string& name,const vec4& val)
{
    Use(true);
    const GLchar* attName = name.c_str();
    GLint uniform = glGetUniformLocation(prog, attName);
    if(uniform == -1)
        throw runtime_error("Can't acces uniform");
    glUniform4f(uniform , val.r,val.g,val.b,val.a);
    Use(false);
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
void Program::Use(bool val)
{
    if(val)
    {
        glUseProgram(prog);
    }
    else
        glUseProgram(0);
}
void Program::Use(bool val , string progName)
{
    Program* p = GetProgramIns(progName);
    if(val && p != nullptr)
    {
        glUseProgram(p->prog);
    }
    else
        glUseProgram(0);
}
GLuint& Program::GetProgram()
{
    return prog;
}
GLuint& Program::GetProgram(string progName)
{
    for(Program* p : programs)
        if(p->name == progName)
            return p->prog;

    return (*dProg);
}
Program* Program::GetProgramIns(string progName)
{
    for(Program* p : programs)
        if(p->name == progName)
            return p;

    return nullptr;
}
