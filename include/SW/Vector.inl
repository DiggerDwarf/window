// THIS FILE IS NOT TO BE INCLUDED MANUALLY

template <typename Type>
inline Vec2<Type>::Vec2() :
    x(0),
    y(0)
{
}

template <typename Type>
inline Vec2<Type>::Vec2(Type all) :
    x(all),
    y(all)
{
}

template <typename Type>
inline Vec2<Type>::Vec2(Type x_, Type y_) :
    x(x_),
    y(y_)
{
}

template <typename Type>
template <typename otherType>
inline Vec2<Type>::Vec2(const Vec2<otherType> &other) :
    x(static_cast<otherType>(other.x)),
    y(static_cast<otherType>(other.y))
{
}

template <typename Type>
inline float Vec2<Type>::length() const
{
    return sqrtf(this->x*this->x + this->y*this->y);
}

template <typename Type>
inline void Vec2<Type>::normalize()
{
    *this /= this->length();
}

template <typename Type>
inline Vec2<Type> Vec2<Type>::normalized() const
{
    return *this / this->length();
}

template <typename Type>
inline Vec2<Type> Vec2<Type>::operator+(const Vec2<Type>& other) const
{
    return Vec2<Type>(this->x + other.x, this->y + other.y);
}

template <typename Type>
inline Vec2<Type> Vec2<Type>::operator-(const Vec2<Type>& other) const
{
    return Vec2<Type>(this->x - other.x, this->y - other.y);
}

template <typename Type>
inline Vec2<Type> Vec2<Type>::operator*(const Vec2<Type>& other) const
{
    return Vec2<Type>(this->x * other.x, this->y * other.y);
}

template <typename Type>
inline Vec2<Type> Vec2<Type>::operator/(const Vec2<Type>& other) const
{
    return Vec2<Type>(this->x / other.x, this->y / other.y);
}

template <typename Type>
inline Vec2<Type> Vec2<Type>::operator*(const Type other) const
{
    return Vec2<Type>(this->x * other, this->y * other);
}

template <typename Type>
inline Vec2<Type> Vec2<Type>::operator/(const Type other) const
{
    return Vec2<Type>(this->x / other, this->y / other);
}

template <typename Type>
inline void Vec2<Type>::operator+=(const Vec2<Type>& other)
{
    this->x += other.x;
    this->y += other.y;
}

template <typename Type>
inline void Vec2<Type>::operator-=(const Vec2<Type>& other)
{
    this->x -= other.x;
    this->y -= other.y;
}

template <typename Type>
inline void Vec2<Type>::operator*=(const Vec2<Type>& other)
{
    this->x *= other.x;
    this->y *= other.y;
}

template <typename Type>
inline void Vec2<Type>::operator/=(const Vec2<Type>& other)
{
    this->x /= other.x;
    this->y /= other.y;
}

template <typename Type>
inline void Vec2<Type>::operator*=(const Type other)
{
    this->x *= other;
    this->y *= other;
}

template <typename Type>
inline void Vec2<Type>::operator/=(const Type other)
{
    this->x /= other;
    this->y /= other;
}

template <typename Type>
inline Vec3<Type>::Vec3() :
    x(0),
    y(0),
    z(0)
{
}

template <typename Type>
inline Vec3<Type>::Vec3(Type all) :
    x(all),
    y(all),
    z(all)
{
}

template <typename Type>
inline Vec3<Type>::Vec3(Type x_, Type y_, Type z_) :
    x(x_),
    y(y_),
    z(z_)
{
}

template <typename Type>
template <typename otherType>
inline Vec3<Type>::Vec3(const Vec3<otherType> &other) :
    x(static_cast<otherType>(other.x)),
    y(static_cast<otherType>(other.y)),
    z(static_cast<otherType>(other.z))
{
}

template <typename Type>
inline float Vec3<Type>::length() const
{
    return sqrtf(this->x*this->x + this->y*this->y + this->z*this->z);
}

template <typename Type>
inline void Vec3<Type>::normalize()
{
    *this /= this->length();
}

template <typename Type>
inline Vec3<Type> Vec3<Type>::normalized() const
{
    return *this / this->length();
}

template <typename Type>
inline Vec3<Type> Vec3<Type>::operator+(const Vec3<Type>& other) const
{
    return Vec3<Type>(this->x + other.x, this->y + other.y, this->z + other.z);
}

template <typename Type>
inline Vec3<Type> Vec3<Type>::operator-(const Vec3<Type>& other) const
{
    return Vec3<Type>(this->x - other.x, this->y - other.y, this->z - other.z);
}

template <typename Type>
inline Vec3<Type> Vec3<Type>::operator*(const Vec3<Type>& other) const
{
    return Vec3<Type>(this->x * other.x, this->y * other.y, this->z * other.z);
}

template <typename Type>
inline Vec3<Type> Vec3<Type>::operator/(const Vec3<Type>& other) const
{
    return Vec3<Type>(this->x / other.x, this->y / other.y, this->z / other.z);
}

template <typename Type>
inline Vec3<Type> Vec3<Type>::operator*(const Type other) const
{
    return Vec3<Type>(this->x * other, this->y * other, this->z * other);
}

template <typename Type>
inline Vec3<Type> Vec3<Type>::operator/(const Type other) const
{
    return Vec3<Type>(this->x / other, this->y / other, this->z / other);
}

template <typename Type>
inline void Vec3<Type>::operator+=(const Vec3<Type>& other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
}

template <typename Type>
inline void Vec3<Type>::operator-=(const Vec3<Type>& other)
{
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
}

template <typename Type>
inline void Vec3<Type>::operator*=(const Vec3<Type>& other)
{
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
}

template <typename Type>
inline void Vec3<Type>::operator/=(const Vec3<Type>& other)
{
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
}

template <typename Type>
inline void Vec3<Type>::operator*=(const Type other)
{
    this->x *= other;
    this->y *= other;
    this->z *= other;
}

template <typename Type>
inline void Vec3<Type>::operator/=(const Type other)
{
    this->x /= other;
    this->y /= other;
    this->z /= other;
}

template <typename Type>
inline Vec4<Type>::Vec4() :
    x(0),
    y(0),
    z(0),
    w(0)
{
}

template <typename Type>
inline Vec4<Type>::Vec4(Type all) :
    x(all),
    y(all),
    z(all),
    w(all)
{
}

template <typename Type>
inline Vec4<Type>::Vec4(Type x_, Type y_, Type z_, Type w_) :
    x(x_),
    y(y_),
    z(z_),
    w(w_)
{
}

template <typename Type>
template <typename otherType>
inline Vec4<Type>::Vec4(const Vec4<otherType> &other) :
    x(static_cast<otherType>(other.x)),
    y(static_cast<otherType>(other.y)),
    z(static_cast<otherType>(other.z)),
    w(static_cast<otherType>(other.w))
{
}

template <typename Type>
inline float Vec4<Type>::length() const
{
    return sqrtf(this->x*this->x + this->y*this->y + this->z*this->z + this->w*this->w);
}

template <typename Type>
inline void Vec4<Type>::normalize()
{
    *this /= this->length();
}

template <typename Type>
inline Vec4<Type> Vec4<Type>::normalized() const
{
    return *this / this->length();
}

template <typename Type>
inline Vec4<Type> Vec4<Type>::operator+(const Vec4<Type>& other) const
{
    return Vec4<Type>(this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w);
}

template <typename Type>
inline Vec4<Type> Vec4<Type>::operator-(const Vec4<Type>& other) const
{
    return Vec4<Type>(this->x - other.x, this->y - other.y, this->z - other.z, this->w - other.w);
}

template <typename Type>
inline Vec4<Type> Vec4<Type>::operator*(const Vec4<Type>& other) const
{
    return Vec4<Type>(this->x * other.x, this->y * other.y, this->z * other.z, this->w * other.w);
}

template <typename Type>
inline Vec4<Type> Vec4<Type>::operator/(const Vec4<Type>& other) const
{
    return Vec4<Type>(this->x / other.x, this->y / other.y, this->z / other.z, this->w / other.w);
}

template <typename Type>
inline Vec4<Type> Vec4<Type>::operator*(const Type other) const
{
    return Vec4<Type>(this->x * other, this->y * other, this->z * other, this->w * other);
}

template <typename Type>
inline Vec4<Type> Vec4<Type>::operator/(const Type other) const
{
    return Vec4<Type>(this->x / other, this->y / other, this->z / other, this->w / other);
}

template <typename Type>
inline void Vec4<Type>::operator+=(const Vec4<Type>& other)
{
    this->x += other.x;
    this->y += other.y;
    this->z += other.z;
    this->w += other.w;
}

template <typename Type>
inline void Vec4<Type>::operator-=(const Vec4<Type>& other)
{
    this->x -= other.x;
    this->y -= other.y;
    this->z -= other.z;
    this->w -= other.w;
}

template <typename Type>
inline void Vec4<Type>::operator*=(const Vec4<Type>& other)
{
    this->x *= other.x;
    this->y *= other.y;
    this->z *= other.z;
    this->w *= other.w;
}

template <typename Type>
inline void Vec4<Type>::operator/=(const Vec4<Type>& other)
{
    this->x /= other.x;
    this->y /= other.y;
    this->z /= other.z;
    this->w /= other.w;
}

template <typename Type>
inline void Vec4<Type>::operator*=(const Type other)
{
    this->x *= other;
    this->y *= other;
    this->z *= other;
    this->w *= other;
}

template <typename Type>
inline void Vec4<Type>::operator/=(const Type other)
{
    this->x /= other;
    this->y /= other;
    this->z /= other;
    this->w /= other;
}
