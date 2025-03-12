#ifndef __View_hpp_INCLUDED
#define __View_hpp_INCLUDED

#include <SW/Config.hpp>

#include <SW/Vector.hpp>

namespace sw
{

class SW_API Rotation
{
public:
    fVec3 axis;
    float angle;
    
    Rotation() = default;
    Rotation(fVec3 axis, float angle);

    void rotate(fVec3 axis, float angle);

    Rotation operator+(const Rotation& other) const;
    void operator+=(const Rotation& other);
};

class Quaternion
{
    friend class Rotation;
    float x, i, j, k;

    Quaternion();
    Quaternion(float x, float i, float j, float k);
    Quaternion(const fVec3& axis, float angle);

    Quaternion operator*(const Quaternion& other) const;
    void operator*=(const Quaternion& other);

    Rotation toRotation() const;
};

struct View
{
    enum Projection
    {
        Orthographic,
        Perspective
    };
    Rotation    rotation;
    fVec3       position;
    float       fovY;
    float       nearPlane;
    float       farPlane;
    Projection  type;
};

}   // namespace sw

#endif // __View_hpp_INCLUDED