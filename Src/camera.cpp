#include "camera.h"

Camera::Camera(int x,int y)
{
    name = "Main Camera";
    aspectRatio = 1.7f;//  x / y;
    GenerateMatrix();
}
void Camera::uPosition(vec3 val)
{
    position = val;
    GenerateMatrix();
}
void Camera::aPosition(vec3 val)
{
    position += val;
    GenerateMatrix();
}
void Camera::uLookTarget(vec3 val)
{
    lookTarget = val;
    GenerateMatrix();
}
void Camera::aLookTarget(vec3 val)
{
    lookTarget += val;
    GenerateMatrix();
}
void Camera::uRotate(vec3 val)
{
    rotation = val;
    GenerateMatrix();
}
void Camera::aRotate(vec3 val)
{
    rotation += val;
    GenerateMatrix();
}
void Camera::GenerateMatrix()
{
    look = lookAt(position,(lookTarget), vec3(0,1,0));
    projection = perspective<float>(50.0, aspectRatio, 0.1, 20.0);
    camera = projection * look;
}
const mat4& Camera::GetMatrix()
{
    return (camera);
}
const vec3 Camera::GetLook()
{
    return lookTarget;
}
const vec3 Camera::GetPosition()
{
    return position;
}
