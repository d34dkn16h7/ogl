#include "editor.h"

void Editor::Update()
{
    if(glfwGetKey('F') && onEdit != nullptr)
        FocusToObject();
    if( glfwGetKey(GLFW_KEY_LCTRL) && Input::isMousePressed(0) )
        SelectObject();
    if(glfwGetKey(GLFW_KEY_DEL) && onEdit != nullptr) // Delete
    {
        delete onEdit;
        onEdit = nullptr;
    }

    if(glfwGetKey('1'))
        mode = EditMode::PositionEdit;
    if(glfwGetKey('2'))
        mode = EditMode::ScaleEdit;
    if(glfwGetKey('3'))
        mode = EditMode::RotationEdit;   // Empty
    if(glfwGetKey('4'))
        mode = EditMode::ColorEdit;   // Empty


    if(Input::isMouse(0) && onEdit != nullptr)
        Edit();
    if(Input::isMousePressed(1))
        PutObject();

    if(Input::isMouse(2))
        MoveCam();

    if(Input::mouseWDelta != 0)
        Renderer::sCamera()->aPosition( vec3(0,0,Input::mouseWDelta * -.1f) );
}
void Editor::Edit()
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
        if(glfwGetKey(GLFW_KEY_LSHIFT) )
        {
            float fac = (val.x + val.y) / (float)2;
            onEdit->aScale( fac );
        }
        else
        {
            onEdit->aScale( vec3(val.x , val.y , 0) );
        }
        break;
    }
}
void Editor::PutObject()
{
    onEdit = new GameObject();

    vec3 nPos = vec3 ( Renderer::sCamera()->GetPosition() + Input::ScreenToWorld3d());
    nPos.z = 0;

    onEdit->uPosition(nPos);
    onEdit->uColor( vec4(-1,0,0,1) );
    targetMap->Put(onEdit);
}
void Editor::SelectObject()
{
    vec3 gPos = vec3 ( Renderer::sCamera()->GetPosition() + Input::ScreenToWorld3d());
    gPos.z = 0;
    onEdit = Collider::Get(gPos);
}
//
void Editor::SetTarget(Map* val)
{
    targetMap = val;
}
// Cam Func
void Editor::MoveCam()
{
    float camZ = Renderer::sCamera()->GetPosition().z;
    vec2 val = Input::mouseDelta;
    if(camZ < 0)
        camZ = (-camZ);
    val *= (camZ * .002f);
    val.x = -val.x;
    Renderer::sCamera()->aPosition(vec3(val.x,val.y,0));
}
void Editor::FocusToObject()
{
    vec3 p = onEdit->GetPosition();
    vec3 camPos = Renderer::sCamera()->GetPosition();

    p.z = camPos.z - (camPos.z * .02f);

    Renderer::sCamera()->uPosition(p);
}
