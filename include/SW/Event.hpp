#ifndef __Event_hpp_INCLUDED
#define __Event_hpp_INCLUDED

#include <SW/Config.hpp>
#include <SW/Keyboard.hpp>
#include <SW/Mouse.hpp>
#include <SW/Vector.hpp>

namespace sw
{

class SW_API Event
{
public:

    enum class Type {
        None = -1,
        Close = 0,
        KeyPress,
        KeyRelease,
        MousePress,
        MouseRelease,
        Resized,
        Text
    };

    struct KeyEvent
    {
        Keyboard::Key   key;
    };
    
    struct MouseEvent
    {
        Mouse::Button   button;
        iVec2           position;
    };

    struct SizeEvent
    {
        iVec2           newSize;
        bool            isMaximized;
        bool            isMinimized;
    };

    struct TextEvent
    {
        char            character;
    };

    Type type;

    union
    {
        KeyEvent        keyInfo;
        MouseEvent      mouseInfo;
        SizeEvent       sizeInfo;
        TextEvent       textInfo;
    };

    inline Event() : type(Type::None) {}
};

}   // namespace sw

#endif // __Event_hpp_INCLUDED
