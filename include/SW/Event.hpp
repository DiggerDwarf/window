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

    enum class EventType {
        None = -1,
        Close = 0,
        KeyPress,
        KeyRelease,
        MousePress,
        MouseRelease
    };

    struct KeyEvent
    {
        Keyboard::Key key;
    };
    
    struct MouseEvent
    {
        Mouse::Button   button;
        iVec2           position;
    };

    EventType type;

    union
    {
        KeyEvent         keyInfo;
        MouseEvent       mouseInfo;
    };

    inline Event() : type(EventType::None) {}
};

}   // namespace sw

#endif // __Event_hpp_INCLUDED
