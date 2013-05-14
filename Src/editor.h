#ifndef EDITOR_H
#define EDITOR_H

#include "map.h"
#include "input.h"
#include "collider.h"
#include "gameObject.h"

enum EditMode
{PositionEdit,ScaleEdit,RotationEdit,ColorEdit};

class Editor
{
private:
    Map* targetMap;
    GameObject* onEdit;
    EditMode mode;

    void PutObject();
public:
    void SetTarget(Map*);
    void Update();
};

#endif // EDITOR_H
