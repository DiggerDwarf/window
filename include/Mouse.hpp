#ifndef __Mouse_hpp_INCLUDED
#define __Mouse_hpp_INCLUDED

#include <Vector.hpp>
#include <windows.h>

namespace sw
{

class Window;

class Mouse
{
public:
    // When modifying this, update Window::setCursor
    enum class Cursor {
        ARROW,
        FINGER,
        CROSS,
        NO
    };

    enum class Button {
        Left,
        Right,
        Middle,
        Extra1,
        Extra2
    };

    static const iVec2 getMousePos();
    static const iVec2 getMousePos(const Window& reference);

    static void setMousePos(iVec2 newPosition);
    static void setMousePos(iVec2 newPosition, const Window& reference);
};

}   // namespace sw

#endif // __Mouse_hpp_INCLUDED