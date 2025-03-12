#ifndef __Color_hpp_INCLUDED
#define __Color_hpp_INCLUDED

#include <SW/Config.hpp>
#include <cstdint>

namespace sw
{

class SW_API Color
{
public:
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;
    std::uint8_t a;
    
    Color(std::uint8_t red = 0, std::uint8_t green = 0, std::uint8_t blue = 0, std::uint8_t alpha = 255);


    static const Color Black;
    static const Color White;
    static const Color Red;
    static const Color Green;
    static const Color Blue;
    static const Color Yellow;
    static const Color Magenta;
    static const Color Cyan;
    static const Color Transparent;

};

SW_API Color operator+(const Color& left, const Color& right);
SW_API Color operator-(const Color& left, const Color& right);
SW_API Color operator*(const Color& left, const Color& right);
SW_API Color operator*(const Color& left, const float right);
SW_API Color operator*(const float left, const Color& right);
SW_API Color operator/(const Color& left, const float right);
SW_API Color operator/(const float left, const Color& right);

SW_API void operator+=(Color& right, const Color& left);
SW_API void operator-=(Color& right, const Color& left);
SW_API void operator*=(Color& right, const Color& left);
SW_API void operator*=(Color& right, const float left);
SW_API void operator/=(Color& right, const float left);


}   // namesapce sw


#endif // __Color_hpp_INCLUDED