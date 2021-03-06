#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

using namespace glm;

class Transformable
{
private:
public:
    virtual void MoveUpdate() {}
    virtual void RotationUpdate() {}
    virtual void ScaleUpdate() {}
    virtual void GenerateMatrix() {}
};

class Transform
{
private:
    Transformable* parent = nullptr;

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

        if(parent != nullptr)
            parent->GenerateMatrix();
    }
public:
    Transform()
        {MakeMatrix();}
    Transform(Transformable* t) : parent(t)
        {MakeMatrix();}

    /// Add
    void aPosition(const vec3& val)
        {mPosition += val;MakeMatrix();}
    void aRotation(const vec3& val)
        {mRotation += val;MakeMatrix();}
    void aScale(const vec3& val)
        {mScale += val;MakeMatrix();}
    /// Set
    void uPosition(const vec3& val)
        {mPosition = val;MakeMatrix();}
    void uRotation(const vec3& val)
        {mRotation = val;MakeMatrix();}
    void uScale(const vec3& val)
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
