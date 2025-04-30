#include <SW/View.hpp>

#include <cmath>

namespace sw
{

Quaternion::Quaternion() :
    x(0), i(0), j(0), k(1)
{
}

Quaternion::Quaternion(float x, float i, float j, float k) :
    x(x), i(i), j(j), k(k)
{
}

Quaternion::Quaternion(const fVec3 &axis, float angle)
{
    float halfAngle = angle / 2.0F;
    float sinHalfAngle = sin(halfAngle);
    this->x = cos(halfAngle);
    this->i = axis.x * sinHalfAngle;
    this->j = axis.y * sinHalfAngle;
    this->k = axis.z * sinHalfAngle;
}

Quaternion Quaternion::operator*(const Quaternion &other) const
{
    return Quaternion (
        this->x*other.x - this->i*other.i - this->j*other.j - this->k*other.k,
        this->x*other.i + this->i*other.x + this->j*other.k - this->k*other.j,
        this->x*other.j - this->i*other.k + this->j*other.x + this->k*other.i,
        this->x*other.k + this->i*other.j - this->j*other.i + this->k*other.x
    );
}

void Quaternion::operator*=(const Quaternion &other)
{
    *this = *this * other;
}

Rotation Quaternion::toRotation() const
{
if (this->i == 0 && this->j == 0 && this->k == 0) {
        return Rotation(fVec3(0, 0, 1), 0);
    }
    float imaginaryLength = sqrt(this->i*this->i + this->j*this->j + this->k*this->k);
    return Rotation (
        fVec3(this->i/imaginaryLength, this->j/imaginaryLength, this->k/imaginaryLength),
        2.0F * atan2f(imaginaryLength, this->x)
    );
}

Rotation::Rotation() :
    axis(0, 0, 1), angle(0)
{
}

Rotation::Rotation(fVec3 axis, float angle) :
    axis(axis.normalized()), angle(angle)
{
}

void Rotation::rotate(fVec3 axis, float angle)
{
    *this = (Quaternion(this->axis, this->angle) * Quaternion(axis.normalized(), angle)).toRotation();
}

Rotation Rotation::operator+(const Rotation &other) const
{
    Rotation copy = *this;
    copy += other;
    return copy;
}

void Rotation::operator+=(const Rotation &other)
{
    this->rotate(other.axis, other.angle);
}

}   // namespace sw

