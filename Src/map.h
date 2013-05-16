#ifndef MAP_H
#define MAP_H

#include <stdexcept>
#include <fstream>
#include <string>
#include <vector>
#include "gameObject.h"

using namespace std;

class GameObject;
class Map
{
private:
    vector<GameObject*> data;
    void MakeMap(string);
    bool isObject(string);
public:
    static Map* ins;
    void LoadMap(string);
    void SaveMap(string);
    void Put(GameObject*);
    void Pop(GameObject*);
};

#endif // MAP_H
