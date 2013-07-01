#ifndef PREFAB_H
#define PREFAB_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T>
class Prefab
{
private:
    static vector<T*> store;
public:
    string data;
    string name;
    string fileName;

    virtual void LoadPrefab(T*,string) = 0;
};

#endif // PREFAB_H
