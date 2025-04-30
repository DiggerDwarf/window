#ifndef __Keyboard_hpp_INCLUDED
#define __Keyboard_hpp_INCLUDED


#include <SW/Config.hpp>


namespace sw
{

class SW_API Keyboard
{
public:
    // The Num[X] are the numbers & symbols at the top of the keyboard
    enum class Key {
        Unkown = -1,
        A = 0,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,

        Num0,
        Num1,
        Num2,
        Num3,
        Num4,
        Num5,
        Num6,
        Num7,
        Num8,
        Num9,

        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,
        F16,
        F17,
        F18,
        F19,
        F20,
        F21,
        F22,
        F23,
        F24,

        Numpad0,
        Numpad1,
        Numpad2,
        Numpad3,
        Numpad4,
        Numpad5,
        Numpad6,
        Numpad7,
        Numpad8,
        Numpad9,

        LSuper,
        RSuper,
        LControl,
        RControl,
        LAlt,
        RAlt,
        LShift,
        RShift,

        Left,
        Up,
        Right,
        Down,

        PageUp,
        PageDown,
        Home,
        End,

        Backspace,
        Delete,
        Tab,
        Enter,
        Space,
        Escape,

        CapsLock,
        NumLock,

        Equal

    };

    static Key winCodeToKey(WPARAM key, LPARAM info);
    static int keyToWinCode(Key key);

    static bool isKeyPressed(Key key);

};

}   // namespace sw

#endif // __Keyboard_hpp_INCLUDED