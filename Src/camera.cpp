#include "camera.h"

Camera* Camera::MainCamera;

Camera::Camera(int x,int y)
{
    MainCamera = this;
    ScreenSize = vec2(x,y);
    aspectRatio = (float)x / (float)y;
    GenerateMatrix();
}
void Camera::GenerateMatrix()
{
    look = lookAt(position,(position + lookTarget), vec3(0,1,0));
    projection = perspective<float>(60, aspectRatio, 0.1, 100.0);
    camera = projection * look;
}
//SET
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
//GET
const mat4& Camera::GetMatrix()
{
    return (camera);
}
mat4 Camera::Matrix()
{
    return camera;
}
mat4 Camera::GetPerspective()
{
    return perspective<float>(60, aspectRatio, 0.1, 100.0);
}
vec3 Camera::GetLook()
{
    return lookTarget;
}
vec3 Camera::GetPosition()
{
    return position;
}
float Camera::GetAspectRatio()
{
    return aspectRatio;
}
