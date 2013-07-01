#ifndef MAP_H
#define MAP_H

#include <glm/glm.hpp>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using namespace glm;

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
