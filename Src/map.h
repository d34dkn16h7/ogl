#ifndef MAP_H
#define MAP_H

#include <stdexcept>
#include <fstream>
#include <string>
#include <vector>
#include "gameObject.h"

using namespace std;

class Map
{
private:
    vector<GameObject*> data;
    void MakeMap(string);
    bool isObject(string);
public:
    void LoadMap(string);
    void Put(GameObject*);
};

#endif // MAP_H
