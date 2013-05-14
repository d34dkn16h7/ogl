#include "editor.h"

void Editor::SetTarget(Map* val)
{
    targetMap = val;
}
void Editor::Update()
{
    if(glfwGetKey('F') && onEdit != nullptr)
    {
        vec3 p = onEdit->GetPosition();
        p.z = Renderer::sCamera()->GetPosition().z;
        Renderer::sCamera()->uPosition(p);
    }
    if(glfwGetKey('1'))
    {mode = EditMode::PositionEdit;}
    if(glfwGetKey('2'))
    {mode = EditMode::ScaleEdit;}
    /*if(glfwGetKey('3'))
    {mode = EditMode::RotationEdit;}
    if(glfwGetKey('4'))
    {mode = EditMode::ColorEdit;}*/


    if(Input::isMouse(0) && onEdit != nullptr) //Edit
    {
        vec2 val = Input::mouseDelta;
        float camZ = Renderer::sCamera()->GetPosition().z;
        switch (mode)
        {
        case EditMode::PositionEdit:
            if(camZ < 0)
                camZ = (-camZ);
            val *= (camZ * .002f);
            onEdit->aPosition(vec3(val.x,-val.y,0));
            break;
        case EditMode::ScaleEdit:
            val *= .01f;
            float fac = (val.x + val.y) / (float)2;
            onEdit->aScale( fac );
            break;
        }
    }
    if(Input::isMousePressed(1)) //PutObject
        PutObject();

    if(Input::isMouse(2)) // Move camera
    {
        float camZ = Renderer::sCamera()->GetPosition().z;
        vec2 val = Input::mouseDelta;
        if(camZ < 0)
                camZ = (-camZ);
        val *= (camZ * .002f);
        val.x = -val.x;
        Renderer::sCamera()->aPosition(vec3(val.x,val.y,0));
    }

    if(Input::mouseWDelta != 0)
        Renderer::sCamera()->aPosition( vec3(0,0,Input::mouseWDelta * -.1f) );
}
void Editor::PutObject()
{
    onEdit = new GameObject();
    //cout << v.x << ":" << v.y << endl;
    vec3 nPos = vec3 ( Renderer::sCamera()->GetPosition() + Input::ScreenToWorld3d());
    nPos.z = 0;
    onEdit->uPosition(nPos);
    onEdit->uColor( vec4(-1,0,0,1) );
    targetMap->Put(onEdit);
}
