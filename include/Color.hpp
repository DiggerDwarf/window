#ifndef __Color_hpp_INCLUDED
#define __Color_hpp_INCLUDED

#include <cstdint>

namespace sw
{

class Color
{
public:
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
    
    Color(uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0, uint8_t alpha = 255);


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

Color operator+(const Color& left, const Color& right);
Color operator-(const Color& left, const Color& right);
Color operator*(const Color& left, const Color& right);

void operator+=(Color& right, const Color& left);
void operator-=(Color& right, const Color& left);
void operator*=(Color& right, const Color& left);

}   // namesapce sw


#endif // __Color_hpp_INCLUDED