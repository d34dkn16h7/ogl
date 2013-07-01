#include "tools.h"

using namespace Tools;

void Token::MakeToken() /// Based on space | tab | new line
{
    string cVal = "";
    tokens.push_back("#firstToken");
    for (char ch : raw)
    {
        if(ch == ' ' || ch == '\n' || ch == '\t')
        {
            if(cVal != "")
            {
                tokens.push_back(cVal);
                cVal = "";
            }
        }
        else
            cVal += ch;
    }

    if(cVal != "")
        tokens.push_back(cVal);

    tokens.push_back("#endToken");
}

string Token::Next() /// Return next token and update current token
{
    if(tokens.size() > indexer + 1)
        indexer++;
    return tokens[indexer];
}

string Token::Peek(int i) /// Return indexer + i token
{
    int nIndexer = indexer + i;
    if(tokens.size() >= nIndexer)
    {
        if(nIndexer >= 1)
            return tokens[nIndexer];
        else
            return "#firstToken";
    }
    else
        return "#endToken";
}

string Token::Current() /// Return current token
{
    return tokens[indexer];
}

vec2 Token::GetNVec2()
{
    vec2 tVec(0,0);

    if( CanGVec3() )
    {
        tVec.x = atof(Next().c_str());
        tVec.y = atof(Next().c_str());
    }

    return tVec;
}

vec3 Token::GetNVec3()
{
    vec3 tVec(0,0,0);

    if( CanGVec3() )
    {
        tVec.x = atof(Next().c_str());
        tVec.y = atof(Next().c_str());
        tVec.z = atof(Next().c_str());
    }

    return tVec;
}

bool Token::CanGNum()
{
    return Str::isNum( Peek(1) );
}

bool Token::CanGVec2()
{
    return (CanGNum() && Str::isNum( Peek(2) ));
}

bool Token::CanGVec3()
{
    return (CanGVec2() && Str::isNum( Peek(3) ));
}


void Token::PrintTokens() /// Print all tokens
{
    for(string val : tokens)
        cout << val << endl;
}
