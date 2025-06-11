#include <SW/Font.hpp>
#include <iostream>

int main()
{
    sw::Font::open("consolas.ttf", "consolas");

    sw::Font::close("consolas");
}