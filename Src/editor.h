#ifndef EDITOR_H
#define EDITOR_H

#include "map.h"
#include "gameObject.h"

enum EditMode
{PositionEdit,ScaleEdit,RotationEdit,ColorEdit};

class Editor
{
private:
    bool isMultyEdit;
    vector<GameObject*> selection;
    Map* targetMap;
    GameObject* onEdit;
    EditMode mode;

    void Edit();
    void CommandLine();
    void PutObject();
    void DeleteObject();
    void SelectObjects();
    void UpdateSelections(const vector<GameObject*> );
    void RemoveSelection(GameObject*);

    void aScale(vec3);
    void aPosition(vec3);

    void MoveCam(); // m-click
public:
    void SetTargetMap(Map*);
    void Update();
    bool isSelected(GameObject*);
};

#endif // EDITOR_H
