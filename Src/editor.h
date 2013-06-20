#ifndef EDITOR_H
#define EDITOR_H

#include <glm/glm.hpp>
#include <vector>

using namespace std;
using namespace glm;

enum EditMode
{PositionEdit,ScaleEdit,RotationEdit,ColorEdit};

class Map;
class GameObject;
class Editor
{
private:
    bool isMultyEdit;
    vector<GameObject*> selection;
    Map* targetMap;
    GameObject* onEdit;
    EditMode mode;

    void Edit();
    void PutObject();
    void DeleteObject();
    void SelectObjects();
    void UpdateSelection(GameObject*);
    void UpdateSelections(const vector<GameObject*> );
    void RemoveSelection(GameObject*);
    void ClearSelection();

    void aScale(vec3);
    void aPosition(vec3);

    void MoveCam();
public:
    void SetTargetMap(Map*);
    void Update();
    bool isSelected(GameObject*);
};

#endif // EDITOR_H
