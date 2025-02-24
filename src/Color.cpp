#include <Color.hpp>

namespace sw
{

const Color Color::Black(0, 0, 0);
const Color Color::White(255, 255, 255);
const Color Color::Red(255, 0, 0);
const Color Color::Green(0, 255, 0);
const Color Color::Blue(0, 0, 255);
const Color Color::Yellow(255, 255, 0);
const Color Color::Magenta(255, 0, 255);
const Color Color::Cyan(0, 255, 255);
const Color Color::Transparent(0, 0, 0, 0);

Color::Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) :
    r(red),
    g(green),
    b(blue),
    a(alpha)
{
}

Color operator+(const Color &left, const Color &right)
{
    return Color(
        left.r + right.r,
        left.g + right.g,
        left.b + right.b,
        left.a + right.a
    );
}

Color operator-(const Color &left, const Color &right)
{
    return Color(
        left.r - right.r,
        left.g - right.g,
        left.b - right.b,
        left.a - right.a
    );
}

Color operator*(const Color &left, const Color &right)
{
    return Color(
        (left.r * right.r) / 255,
        (left.g * right.g) / 255,
        (left.b * right.b) / 255,
        (left.a * right.a) / 255
    );
}

void operator+=(Color &right, const Color &left)
{
    right = right + left;
}

void operator-=(Color &right, const Color &left)
{
    right = right - left;
}

void operator*=(Color &right, const Color &left)
{
    right = right * left;
}

} // namespace sw
