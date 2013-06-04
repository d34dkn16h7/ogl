#include "input.h"
#include "camera.h"
#include "editor.h"
#include "physics.h" // remove this later
#include "collider.h"

void Editor::Update()
{
    isMultyEdit = glfwGetKey( GLFW_KEY_LCTRL );

    /*if(glfwGetKey('F'))
        FocusToObject();*/

    if(Input::isMousePressed(0) && (((Input::mouseDelta.x + Input::mouseDelta.y) / 2) < .1f) )
        SelectObjects();

    if(glfwGetKey(GLFW_KEY_DEL))
    {
        DeleteObject();
        //delete onEdit;onEdit = nullptr;
    }
    if(glfwGetKey(GLFW_KEY_F2))
        CommandLine();

    if(glfwGetKey('1'))
        mode = EditMode::PositionEdit;
    if(glfwGetKey('2'))
        mode = EditMode::ScaleEdit;
    if(glfwGetKey('3'))
        mode = EditMode::RotationEdit;   // Empty
    if(glfwGetKey('4'))
        mode = EditMode::ColorEdit;   // Empty


    if(Input::isMouse(0))
        Edit();
    if(Input::isMousePressed(1))
        PutObject();

    if(Input::isMouse(2))
        MoveCam();

    if(Input::mouseWDelta != 0)
        Camera::MainCamera->aPosition( vec3(0,0,Input::mouseWDelta * -.1f) );
}
void Editor::Edit()
{
    vec2 val = Input::mouseDelta;
    float camZ = Camera::MainCamera->GetPosition().z;

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
        if(glfwGetKey(GLFW_KEY_LSHIFT) )
        {
            float fac = (val.x + val.y) / 2;
            aScale( vec3(fac,fac,fac) );
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
void Editor::CommandLine() // look at the mess
{
    /*
    string currentCommand = "";
    cout << " -> ";
    cin >> currentCommand;

    if(currentCommand == "add")
    {
        string componentName;
        cout << " -> Enter component name : ";
        cin >> componentName;
        if(componentName == "physics")
        {
            if(onEdit != nullptr)
            {
                onEdit->physics = new Physics(onEdit);
                onEdit->physics->AddConstantForce(vec3(0,-.01f,0));
                cout << endl << " -> Component added" << endl;
            }
            else
                cout << endl << " -> Couldn't add component" << endl;
        }
    }
    else if(currentCommand == "del")
    {
        if(onEdit != nullptr && onEdit->physics != nullptr)
            delete onEdit->physics;
    }*/
}
void Editor::PutObject()
{
    if(!isMultyEdit)
        selection.clear();

    GameObject* edit = new GameObject();
    vec3 nPos = vec3 ( Camera::MainCamera->GetPosition() + Input::ScreenToWorld3d());
    nPos.z = 0;
    edit->uPosition(nPos);
    edit->uColor( vec4(-1,0,0,1) );
    targetMap->Put(edit);
    selection.push_back(edit);
}
void Editor::DeleteObject()
{
    for(GameObject* gmo : selection)
        delete gmo;

    selection.clear();
}
void Editor::SelectObjects()
{
    vec3 gPos = vec3 ( Camera::MainCamera->GetPosition() + Input::ScreenToWorld3d());
    gPos.z = 0;

    if(!isMultyEdit)
        selection.clear();

    UpdateSelections( (Collider::GetAll(gPos)) );
}
void Editor::UpdateSelections( vector<GameObject*> val)
{
     for(GameObject* gmo : val)
        if(!isSelected(gmo))
            selection.push_back(gmo);
        else
            RemoveSelection(gmo);
}
void Editor::RemoveSelection(GameObject* obj)
{
    for(unsigned int i = 0;i < selection.size();i++)
    {
        if(selection[i] == obj)
        {
            selection.erase(selection.begin() + i);
        }
    }
}
void Editor::SetTargetMap(Map* val)
{
    targetMap = val;
}
void Editor::aPosition(vec3 val)
{
    for(GameObject* gmo : selection)
        gmo->aPosition(val);
}
void Editor::aScale(vec3 val)
{
    for(GameObject* gmo : selection)
        gmo->aScale(val);
}
void Editor::MoveCam()
{
    float camZ = Camera::MainCamera->GetPosition().z;
    vec2 val = Input::mouseDelta;
    if(camZ < 0)
        camZ = (-camZ);
    val *= (camZ * .002f);
    val.x = -val.x;
    Camera::MainCamera->aPosition(vec3(val.x,val.y,0));
}
void Editor::FocusToObject()
{
    /*
    vec3 p = onEdit->GetPosition();
    vec3 camPos = Camera::MainCamera->GetPosition();

    p.z = camPos.z - (camPos.z * .02f);

    Camera::MainCamera->uPosition(p);*/
}
bool Editor::isSelected(GameObject* val)
{
    for(GameObject* gmo : selection)
        if(gmo == val)
            return true;

    return false;
}
