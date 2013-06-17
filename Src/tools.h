#ifndef TOOLS_H
#define TOOLS_H

#include <glm/glm.hpp>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;
using namespace glm;
enum ComponentType
{
    C_Physics,
    C_Collider
};
namespace Tools
{
    class Rect
    {
    public:
        float xmi,xma;
        float ymi,yma;
        Rect() : xmi(-1), xma(1), ymi(-1), yma(1) {}
        Rect(float xm1,float ym1,float xm2 , float ym2) : xmi(xm1), xma(xm2), ymi(ym1), yma(ym2) {}
        Rect(float w,float h) : xmi( -(w/2) ), xma( (w/2) ), ymi( -(h/2) ), yma( (h/2) ) {}
    };

    class File
    {
    public:
        static string tLoadFile(string fSrc)
        {
            fstream file(fSrc.c_str());
            if(file.is_open())
            {
                string whole;

                while(!file.eof())
                {
                    int val = file.get();

                    if(val != -1)
                        whole += val;
                }
                return whole;
            }
            else
            {
                //throw  runtime_error("Can't Read File " + fSrc);
                return "";
            }
        }
        static void tSaveFile(string fSrc,string sData)
        {
            fstream file(fSrc.c_str(),std::fstream::trunc | std::fstream::out);
            if(file.is_open())
            {
                file << sData;file.close();
            }
            else
            {
                throw  runtime_error("Can't Read File " + fSrc);
            }
        }
    };
    class Str
    {
    public:
        static void AddHashStreamVec3( stringstream& stream, string hVal, vec3 val, int flag)
        {
            stream << "\t"<< hVal << " " << val.x << " " << val.y << " " << val.z;
            if(flag == 1)
                stream << endl;
        }
        static void AddHashStreamVec4( stringstream& stream, string hVal, vec4 val, int flag)
        {
            stream << "\t"<< hVal << " " << val.x << " " << val.y << " " << val.z << " " << val.w;
            if(flag == 1)
                stream << endl;
        }
        static string ClearWhiteSpaces(const string val)
        {
            string nVal = "";

            for (int i : val)
                if(i != -1 && i != int(' '))
                    nVal += i;

            return nVal;
        }
        static string RemoveFormat(const string val)
        {
            string nVal = "";

            for (int i : val)
                if(i != 13 && i != 10)
                    nVal += i;
                else
                    nVal += 32;

            return nVal;
        }
        static void PrintAscii(const string val)
        {
            for (int i : val)
            {
                cout << i << " . ";
            }
        }
        static void PrintAsciiF(const string val)
        {
            for (int i : val)
            {
                cout << i << ".";
                if (i == 32)
                    cout << " ";
                else if(i == 10)
                    cout << endl;
            }
        }
        static string removeChar(const string val,char c)
        {
            string nVal = "";
            for( int i : val)
                if(i != (int)c)
                    nVal += i;

            return nVal;
        }
    };
    class Token
    {
    private:
        string raw;
    public:
        vector<string> tokens;
        Token(string val)
        {
            raw = val;
            TokenizerSpaceTEST();//PrintTokens();
        }
        void TokenizerTEST()
        {
            string cVal = "";
            for (unsigned char ch : raw)
            {
                if(ch == ':')
                {
                    if(cVal != "")
                    {
                        tokens.push_back(cVal);
                        cVal = "";
                    }
                }
                else if(ch != '{' && ch != '}' && ch != ' ')
                    cVal += ch;
            }
        }
        void TokenizerSpaceTEST()
        {
            string cVal = "";
            bool isSkipping = false;
            for (unsigned char ch : raw)
            {

                if(ch == '#')
                {
                    isSkipping = !isSkipping;
                }

                if(isSkipping) {}
                else if(ch == ' ')
                {
                    if(cVal != "")
                    {
                        tokens.push_back(cVal);
                        cVal = "";
                    }
                }
                else
                {
                    if(ch != '#' && ch != ' ' && ch != 9)
                        cVal += ch;
                }
            }
        }
        void PrintTokens()
        {
            for(string val : tokens)
                cout << val << endl;
        }
    };
}
#endif // TOOLS_H
