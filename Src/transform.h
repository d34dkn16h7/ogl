#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

using namespace glm;

class Transform
{
private:
    vec3 mPosition = vec3(0,0,0);
    vec3 mRotation = vec3(0,0,0);
    vec3 mScale = vec3(1,1,1);

    mat4 mMatrix;
    void MakeMatrix()
    {
        mMatrix = translate(mat4(1.0),mPosition);
        mMatrix *= rotate(mat4(1.0),mRotation.x , vec3(0,1,0));
        mMatrix *= rotate(mat4(1.0),mRotation.y , vec3(1,0,0));
        mMatrix *= scale(mat4(1.0),mScale);
    }
public:
    Transform()
        {MakeMatrix();}
    /// Add
    void aPosition(vec3 val)
        {mPosition += val;MakeMatrix();}
    void aRotation(vec3 val)
        {mRotation += val;MakeMatrix();}
    void aScale(vec3 val)
        {mScale += val;MakeMatrix();}
    /// Set
    void uPosition(vec3 val)
        {mPosition = val;MakeMatrix();}
    void uRotation(vec3 val)
        {mRotation = val;MakeMatrix();}
    void uScale(vec3 val)
        {mScale = val;MakeMatrix();}
    /// Get
    vec3 gPosition() const
        {return mPosition;}
    vec3 gRotation() const
        {return mRotation;}
    vec3 gScale() const
        {return mScale;}
    mat4 gMatrix() const
        {return mMatrix;}
};

#endif // TRANSFORM_H
