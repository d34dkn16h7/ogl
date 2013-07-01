#include "tools.h"

using namespace Tools;

string File::LoadFile(string fileName)
{
    string whole;
    fstream file(fileName.c_str());
    if(file.is_open())
    {
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
        cout << "Can't read file : " + fileName << endl;
        return "";
    }
}
void File::SaveFile(const string& fileName,const string& data)
{
    fstream file(fileName.c_str(),std::fstream::trunc | std::fstream::out);
    if(file.is_open())
    {
        file << data;
        file.close();
    }
    cout << "Can't save file : " + fileName << endl;
}
