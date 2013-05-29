#ifndef EDITOR_H
#define EDITOR_H

#include "map.h"
#include "gameObject.h"

enum EditMode
{PositionEdit,ScaleEdit,RotationEdit,ColorEdit};

class Editor
{
private:
    Map* targetMap;
    GameObject* onEdit;
    EditMode mode;

    void Edit();
    void CommandLine();
    void PutObject();
    void SelectObject();

    void MoveCam();
    void FocusToObject();
public:
    void SetTargetMap(Map*);
    void Update();
    GameObject* GetOnEdit();
};

#endif // EDITOR_H
