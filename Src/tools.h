#ifndef TOOLS_H
#define TOOLS_H

#include <glm/glm.hpp>
#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;
using namespace glm;

namespace Tools
{
    struct Rect
    {
    public:
        float xmi,xma;
        float ymi,yma;
        Rect() : xmi(-1), xma(1), ymi(-1), yma(1) {}
        Rect(float w,float h) : xmi(-w), xma(w), ymi(-h), yma(h) {}
        Rect(float xm1,float ym1,float xm2 , float ym2) : xmi(xm1), xma(xm2), ymi(ym1), yma(ym2) {}
        Rect(const Rect& r)
        {
            xmi = r.xmi;
            xma = r.xma;
            ymi = r.ymi;
            yma = r.yma;
        }
        Rect(const Rect& r, const vec3& s)
        {
            xmi = r.xmi * s.x;
            xma = r.xma * s.x;
            ymi = r.ymi * s.y;
            yma = r.yma * s.y;
        }
        void Scale(const vec3& val)
        {
            xmi = xmi * val.x;
            xma = xma * val.x;
            ymi = ymi * val.y;
            yma = yma * val.y;
        }
        void AddOffset(const vec3& val)
        {
            xmi += val.x;
            xma += val.x;
            ymi += val.y;
            yma += val.y;
        }
    };
    class File
    {
    public:
        static string LoadFile( string);
        static void SaveFile( const string&, const string&);
    };
    class Str
    {
    public:
        static bool isNum( const string&);
        static void AddHashStreamVec3( stringstream&, string, vec3);
        static void AddHashStreamVec4( stringstream&, string, vec4);
        static string ClearWhiteSpaces( const string&);
    };
    class Token
    {
    private:
        unsigned int indexer = 0;
        string raw; /// Raw source string
        void MakeToken(); /// Based on space | tab | new line
    public:
        vector<string> tokens;

        Token( const string&);

        string Next(); /// Return next token and update current token
        string Peek( int); /// Return indexer + i token
        string Current(); /// Return current token

        bool CanGNum();
        bool CanGVec2();
        bool CanGVec3();

        vec2 GetNVec2();
        vec3 GetNVec3();
        void PrintTokens();
    };
}
#endif // TOOLS_H
