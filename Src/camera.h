#ifndef CAMERA_H
#define CAMERA_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

using namespace std;
using namespace glm;

class Camera
{
private:
    int fow;
    float aspectRatio;

    vec3 position = vec3(0,0,15);
    vec3 rotation = vec3(0,0,0);
    vec3 lookTarget = vec3(0,0,-.1f);

    mat4 look;
    mat4 camera;
    mat4 projection;

public:
    vec2 ScreenSize;
    static Camera* MainCamera;
    Camera(int,int);

    void GenerateMatrix();

    void uPosition(vec3);
    void aPosition(vec3);
    void uLookTarget(vec3);
    void aLookTarget(vec3);
    void uRotate(vec3); //sets rotation of the whole scene
    void aRotate(vec3); //rotates the whole scene

    const mat4& GetMatrix();
    mat4 Matrix();
    mat4 GetPerspective();
    vec3 GetLook();
    vec3 GetPosition();
    float GetAspectRatio();
};

#endif // CAMERA_H
