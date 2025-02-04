#ifndef __Event_hpp_INCLUDED
#define __Event_hpp_INCLUDED

class Event
{
public:

    enum EventType {
        WINDOW_CLOSED,
        KEY_INPUT,
        MOUSE_INPUT
    };

    struct Keyboard
    {
        unsigned code;
        bool    alt;
        bool    ctrl;
        bool    shift;
        bool    super;
    };
    
    struct Mouse
    {
        int x;
        int y;
    };

    EventType type;

    union
    {
        Keyboard        keyInfo;
        Mouse           mouseInfo;
    };

};


#endif // __Event_hpp_INCLUDED