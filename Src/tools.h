#ifndef TOOLS_H
#define TOOLS_H

#include <glm/glm.hpp>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace glm;

namespace Tools
{
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
                throw  runtime_error("Can't Read File " + fSrc);
                return "";
            }
        }
        static void tSaveFile(string fSrc,string sData)
        {
            fstream file(fSrc.c_str());
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
        static string ClearWhiteSpaces(const string val)
        {
            string nVal = "";

            for (int i : val)
            {
                if(i != -1 && i != int(' '))
                    nVal += i;
            }

            return nVal;
        }
        static string RemoveFormat(const string val)
        {
            string nVal = "";
            for (int i : val)
            {
                if(i != 13 && i != 10)
                    nVal += i;
                else
                {
                    nVal += 32;
                }
            }
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
            {
                if(i != (int)c)
                    nVal += i;
            }

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

                if(isSkipping)
                {
                }
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
