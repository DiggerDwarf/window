#include <SW/Mouse.hpp>
#include <SW/Window.hpp>

namespace sw
{

const iVec2 Mouse::getMousePos()
{
    iVec2 pos;
    GetCursorPos(reinterpret_cast<LPPOINT>(&pos));
    return pos;
}

const iVec2 Mouse::getMousePos(const Window &reference)
{
    iVec2 pos;
    GetCursorPos(reinterpret_cast<LPPOINT>(&pos));
    return reference.screenToWindow(pos);
}

void Mouse::setMousePos(iVec2 newPosition)
{
    SetCursorPos(newPosition.x, newPosition.y);
}

void Mouse::setMousePos(iVec2 newPosition, const Window &reference)
{
    ClientToScreen(reference.getWin32Handle(), reinterpret_cast<LPPOINT>(&newPosition));
    SetCursorPos(newPosition.x, newPosition.y);
}

}   // namespace sw
