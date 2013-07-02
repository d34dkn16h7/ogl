#ifndef CAMERA_H
#define CAMERA_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "transform.h"

using namespace std;
using namespace glm;

class Camera : Transformable
{
private:
    int fow;
    float aspectRatio;

    vec3 lookTarget = vec3(0,0,-.1f);

    mat4 look;
    mat4 camera;
    mat4 projection;
public:
    Transform transform;
    vec2 ScreenSize;
    static Camera* MainCamera;
    Camera(int,int);

    void GenerateMatrix();

    void uLookTarget(vec3);
    void aLookTarget(vec3);

    mat4 Matrix();
    mat4 GetPerspective();
    float GetAspectRatio();
    const mat4& GetMatrix();
};

#endif // CAMERA_H
