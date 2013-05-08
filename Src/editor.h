#ifndef EDITOR_H
#define EDITOR_H

#include "map.h"
#include "input.h"
#include "gameObject.h"

class Editor
{
private:
    Map* targetMap;
    GameObject* onEdit;

    vec3 ScreenToWorld();
    void PutObject();
public:
    void SetTarget(Map*);
    void Update();
};

#endif // EDITOR_H
