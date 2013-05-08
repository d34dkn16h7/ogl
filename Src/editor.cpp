#include "editor.h"

void Editor::SetTarget(Map* val)
{
    targetMap = val;
}
void Editor::Update()
{
    if(Input::isMousePressed(1))
    {
        onEdit = new GameObject();
        onEdit->uColor( vec4(-1,0,0,0) );
        targetMap->Put(onEdit);
    }

    if(Input::isMouse(2) && onEdit != nullptr)
    {
        vec2 val = Input::mouseDelta;
        val *= .1f;
        onEdit->aRotate(vec3(val.x,val.y,0));
    }

    if(Input::isMouse(0) && onEdit != nullptr)
    {
        vec2 val = Input::mouseDelta;
        val *= .01f;
        onEdit->aPosition(vec3(val.x,-val.y,0));
    }
}
void Editor::PutObject()
{

}
vec3 Editor::ScreenToWorld()
{
    return vec3(0,0,0);
}
