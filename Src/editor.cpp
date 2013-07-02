#include "map.h"
#include "input.h"
#include "camera.h"
#include "editor.h"
#include "physics.h" // remove this later
#include "collider.h" // remove this later
#include "component.h"
#include "gameObject.h"

void Editor::Update()
{
    isMultyEdit = Input::isKey(GLFW_KEY_LEFT_CONTROL);

    if(Input::isMousePressed(0))
        SelectObjects();
    if( Input::isKey(GLFW_KEY_DELETE) )
        DeleteObject();


    if(Input::isMouse(0))
        Edit();
    if(Input::isMousePressed(1))
        PutObject();
    if(Input::isMouse(2))
        MoveCam();

    if( Input::isKey(GLFW_KEY_1) )
        mode = EditMode::PositionEdit;
    if( Input::isKey(GLFW_KEY_2) )
        mode = EditMode::ScaleEdit;
    if( Input::isKey(GLFW_KEY_3) )
        mode = EditMode::RotationEdit;   // Empty
    if( Input::isKey(GLFW_KEY_4) )
        mode = EditMode::ColorEdit;   // Empty

    if(Input::mouseWDelta.y != 0)
        Camera::MainCamera->transform.aPosition( vec3(0,0,Input::mouseWDelta.y * -.4f) );
}
void Editor::Edit()
{
    vec2 val = Input::mouseDelta;
    float camZ = Camera::MainCamera->transform.gPosition().z;

    switch (mode)
    {
    case EditMode::PositionEdit:
        if(camZ < 0)
            camZ = (-camZ);
        val *= (camZ * .002f);
        aPosition(vec3(val.x,-val.y,0));
        break;
    case EditMode::ScaleEdit:
        val *= .01f;
        if( Input::isKey(GLFW_KEY_LEFT_SHIFT) )
        {
            float fac = (val.x + val.y) / 2;
            aScale( vec3(fac,fac,0) );
        }
        else
        {
            aScale( vec3(val.x , val.y , 0) );
        }
        break;
    case EditMode::ColorEdit:
    case EditMode::RotationEdit:
    default:
        break;
    }
}
void Editor::PutObject()
{
    if(!isMultyEdit)
        ClearSelection();

    GameObject* edit = new GameObject();
    edit->isActive = false;
    vec3 nPos = vec3 ( Camera::MainCamera->transform.gPosition() + Input::ScreenToWorld3d());
    nPos.z = 0;
    edit->transform.uPosition(nPos);
    targetMap->Reg(edit);
    UpdateSelection(edit);
}
void Editor::DeleteObject()
{
    for(GameObject* gmo : selection)
        delete gmo;

    selection.clear();
}
void Editor::SelectObjects()
{
    vec3 gPos = vec3 ( Camera::MainCamera->transform.gPosition() + Input::ScreenToWorld3d());
    gPos.z = 0;

    if(!isMultyEdit)
        ClearSelection();

    UpdateSelections( Collider::GetAll(gPos) );
}
void Editor::UpdateSelections(const vector<GameObject*> val)
{
     for(GameObject* gmo : val)
        if(!isSelected(gmo))
        {
            gmo->isActive = false;
            selection.push_back(gmo);
        }
        else
        {
            gmo->isActive = true;
            RemoveSelection(gmo);
        }
}
void Editor::UpdateSelection(GameObject* obj)
{
    if(!isSelected(obj))
    {
        obj->isActive = false;
        selection.push_back(obj);
    }
    else
    {
        obj->isActive = true;
        RemoveSelection(obj);
    }
}
void Editor::RemoveSelection(GameObject* obj)
{
    for(unsigned int i = 0;i < selection.size();i++)
        if(selection[i] == obj)
        {
            obj->isActive = true;
            selection.erase(selection.begin() + i);
        }
}
void Editor::ClearSelection()
{
    for(GameObject* gmo : selection)
        gmo->isActive = true;

    selection.clear();
}
void Editor::SetTargetMap(Map* val)
{
    targetMap = val;
}
void Editor::aPosition(vec3 val)
{
    for(GameObject* gmo : selection)
        gmo->transform.aPosition(val);
}
void Editor::aScale(vec3 val)
{
    for(GameObject* gmo : selection)
        gmo->transform.aScale(val);
}
void Editor::MoveCam()
{
    float camZ = Camera::MainCamera->transform.gPosition().z;
    vec2 val = Input::mouseDelta;
    if(camZ < 0)
        camZ = (-camZ);
    val *= (camZ * .002f);
    val.x = -val.x;
    Camera::MainCamera->transform.aPosition(vec3(val.x,val.y,0));
}
bool Editor::isSelected(GameObject* val)
{
    for(GameObject* gmo : selection)
        if(gmo == val)
            return true;

    return false;
}
