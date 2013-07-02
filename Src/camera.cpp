#include "camera.h"

Camera* Camera::MainCamera;

Camera::Camera(int x,int y) :
    fow(60) , aspectRatio( (float)x / (float)y ) , ScreenSize( vec2(x,y) ) , transform(this)
{
    transform.uPosition(vec3(0,0,15));
    MainCamera = this;
    GenerateMatrix();
}

void Camera::GenerateMatrix()
{
    look = lookAt(transform.gPosition(),(transform.gPosition() + lookTarget), vec3(0,1,0));
    projection = perspective<float>(fow, aspectRatio, 0.1, 100.0);
    camera = projection * look;
}
//SET
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
    return perspective<float>(fow, aspectRatio, 0.1, 100.0);
}

float Camera::GetAspectRatio()
{
    return aspectRatio;
}
