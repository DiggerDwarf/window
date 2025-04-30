#ifndef __Vector_hpp_INCLUDED
#define __Vector_hpp_INCLUDED

#include <SW/Config.hpp>

#ifdef sw_Vector_io
#include <ostream>
#endif

namespace sw
{

template<typename Type>
class Vec2
{
public:
    Type x;
    Type y;

    Vec2();
    Vec2(Type all);
    Vec2(Type x_, Type y_);
    template<typename otherType> Vec2(const Vec2<otherType>& other);

    float length() const;
    void normalize();
    Vec2<Type> normalized() const;

    Vec2<Type> operator+(const Vec2<Type>& other) const;
    Vec2<Type> operator-(const Vec2<Type>& other) const;
    Vec2<Type> operator*(const Vec2<Type>& other) const;
    Vec2<Type> operator/(const Vec2<Type>& other) const;
    Vec2<Type> operator*(const Type other) const;
    Vec2<Type> operator/(const Type other) const;

    void operator+=(const Vec2<Type>& other);
    void operator-=(const Vec2<Type>& other);
    void operator*=(const Vec2<Type>& other);
    void operator/=(const Vec2<Type>& other);
    void operator*=(const Type other);
    void operator/=(const Type other);
};

#ifdef sw_Vector_io
template<typename Type>
inline std::ostream& operator<<(std::ostream& out, const Vec2<Type>& vector)
{
    return out << '<' << vector.x << ", " << vector.y << '>';
}
#endif

typedef Vec2<float>     fVec2;
typedef Vec2<int>       iVec2;
typedef Vec2<unsigned>  uVec2;



template<typename Type>
class Vec3
{
public:
    Type x;
    Type y;
    Type z;

    Vec3();
    Vec3(Type all);
    Vec3(Type x_, Type y_, Type z_);
    template<typename otherType> Vec3(const Vec3<otherType>& other);

    float length() const;
    void normalize();
    Vec3<Type> normalized() const;

    Vec3<Type> operator+(const Vec3<Type>& other) const;
    Vec3<Type> operator-(const Vec3<Type>& other) const;
    Vec3<Type> operator*(const Vec3<Type>& other) const;
    Vec3<Type> operator/(const Vec3<Type>& other) const;
    Vec3<Type> operator*(const Type other) const;
    Vec3<Type> operator/(const Type other) const;

    void operator+=(const Vec3<Type>& other);
    void operator-=(const Vec3<Type>& other);
    void operator*=(const Vec3<Type>& other);
    void operator/=(const Vec3<Type>& other);
    void operator*=(const Type other);
    void operator/=(const Type other);

};

#ifdef sw_Vector_io
template<typename Type>
inline std::ostream& operator<<(std::ostream& out, const Vec3<Type>& vector)
{
    return out << '<' << vector.x << ", " << vector.y << ", " << vector.z << '>';
}
#endif

typedef Vec3<float>     fVec3;
typedef Vec3<int>       iVec3;
typedef Vec3<unsigned>  uVec3;



template<typename Type>
class Vec4
{
public:
    Type x;
    Type y;
    Type z;
    Type w;

    Vec4();
    Vec4(Type all);
    Vec4(Type x_, Type y_, Type z_, Type w_);
    template<typename otherType> Vec4(const Vec4<otherType>& other);

    float length() const;
    void normalize();
    Vec4<Type> normalized() const;

    Vec4<Type> operator+(const Vec4<Type>& other) const;
    Vec4<Type> operator-(const Vec4<Type>& other) const;
    Vec4<Type> operator*(const Vec4<Type>& other) const;
    Vec4<Type> operator/(const Vec4<Type>& other) const;
    Vec4<Type> operator*(const Type other) const;
    Vec4<Type> operator/(const Type other) const;

    void operator+=(const Vec4<Type>& other);
    void operator-=(const Vec4<Type>& other);
    void operator*=(const Vec4<Type>& other);
    void operator/=(const Vec4<Type>& other);
    void operator*=(const Type other);
    void operator/=(const Type other);

};

#ifdef sw_Vector_io
template<typename Type>
inline std::ostream& operator<<(std::ostream& out, const Vec4<Type>& vector)
{
    return out << '<' << vector.x << ", " << vector.y << ", " << vector.z << ", " << vector.w << '>';
}
#endif

typedef Vec4<float>     fVec4;
typedef Vec4<int>       iVec4;
typedef Vec4<unsigned>  uVec4;


#include "Vector.inl"

}   // namespace sw

#endif // __Vector_hpp_INCLUDED

