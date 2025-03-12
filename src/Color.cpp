#include <SW/Color.hpp>

#include <algorithm>

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

Color::Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha) :
    r(red),
    g(green),
    b(blue),
    a(alpha)
{
}

Color operator+(const Color &left, const Color &right)
{
    
    return Color(
        std::min(left.r + right.r, 255),
        std::min(left.g + right.g, 255),
        std::min(left.b + right.b, 255),
        std::min(left.a + right.a, 255)
    );
}

Color operator-(const Color &left, const Color &right)
{
    return Color(
        std::max(left.r - right.r, 0),
        std::max(left.g - right.g, 0),
        std::max(left.b - right.b, 0),
        std::max(left.a - right.a, 0)
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

Color operator*(const Color &left, const float right)
{
    return Color(
        std::clamp(left.r * right, 0.0f, 255.0f),
        std::clamp(left.g * right, 0.0f, 255.0f),
        std::clamp(left.b * right, 0.0f, 255.0f),
        std::clamp(left.a * right, 0.0f, 255.0f)
    );
}

Color operator*(const float left, const Color &right)
{
    return Color(
        std::clamp(left * right.r, 0.0f, 255.0f),
        std::clamp(left * right.g, 0.0f, 255.0f),
        std::clamp(left * right.b, 0.0f, 255.0f),
        std::clamp(left * right.a, 0.0f, 255.0f)
    );
}

Color operator/(const Color &left, const float right)
{
    return Color(
        std::clamp(left.r / right, 0.0f, 255.0f),
        std::clamp(left.g / right, 0.0f, 255.0f),
        std::clamp(left.b / right, 0.0f, 255.0f),
        std::clamp(left.a / right, 0.0f, 255.0f)
    );
}

Color operator/(const float left, const Color &right)
{
    return Color(
        std::clamp(left / right.r, 0.0f, 255.0f),
        std::clamp(left / right.g, 0.0f, 255.0f),
        std::clamp(left / right.b, 0.0f, 255.0f),
        std::clamp(left / right.a, 0.0f, 255.0f)
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

void operator*=(Color &right, const float left)
{
    right = right * left;
}

void operator/=(Color &right, const float left)
{
    right = right / left;
}

} // namespace sw
