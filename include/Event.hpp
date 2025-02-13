#ifndef __Event_hpp_INCLUDED
#define __Event_hpp_INCLUDED

#include <Keyboard.hpp>
#include <Mouse.hpp>

class Event
{
public:

    enum class EventType {
        Close,
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
        int x;
        int y;
    };

    EventType type;

    union
    {
        KeyEvent         keyInfo;
        MouseEvent       mouseInfo;
    };

};


#endif // __Event_hpp_INCLUDED
