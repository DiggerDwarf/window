#include <SW/Keyboard.hpp>


#include <iostream>

namespace sw
{

Keyboard::Key Keyboard::winCodeToKey(WPARAM key, LPARAM info)
{
    switch (key)
    {
        case 'A':           return Keyboard::Key::A;
        case 'B':           return Keyboard::Key::B;
        case 'C':           return Keyboard::Key::C;
        case 'D':           return Keyboard::Key::D;
        case 'E':           return Keyboard::Key::E;
        case 'F':           return Keyboard::Key::F;
        case 'G':           return Keyboard::Key::G;
        case 'H':           return Keyboard::Key::H;
        case 'I':           return Keyboard::Key::I;
        case 'J':           return Keyboard::Key::J;
        case 'K':           return Keyboard::Key::K;
        case 'L':           return Keyboard::Key::L;
        case 'M':           return Keyboard::Key::M;
        case 'N':           return Keyboard::Key::N;
        case 'O':           return Keyboard::Key::O;
        case 'P':           return Keyboard::Key::P;
        case 'Q':           return Keyboard::Key::Q;
        case 'R':           return Keyboard::Key::R;
        case 'S':           return Keyboard::Key::S;
        case 'T':           return Keyboard::Key::T;
        case 'U':           return Keyboard::Key::U;
        case 'V':           return Keyboard::Key::V;
        case 'W':           return Keyboard::Key::W;
        case 'X':           return Keyboard::Key::X;
        case 'Y':           return Keyboard::Key::Y;
        case 'Z':           return Keyboard::Key::Z;

        case '0':           return Keyboard::Key::Num0;
        case '1':           return Keyboard::Key::Num1;
        case '2':           return Keyboard::Key::Num2;
        case '3':           return Keyboard::Key::Num3;
        case '4':           return Keyboard::Key::Num4;
        case '5':           return Keyboard::Key::Num5;
        case '6':           return Keyboard::Key::Num6;
        case '7':           return Keyboard::Key::Num7;
        case '8':           return Keyboard::Key::Num8;
        case '9':           return Keyboard::Key::Num9;

        case VK_F1:         return Keyboard::Key::F1;
        case VK_F2:         return Keyboard::Key::F2;
        case VK_F3:         return Keyboard::Key::F3;
        case VK_F4:         return Keyboard::Key::F4;
        case VK_F5:         return Keyboard::Key::F5;
        case VK_F6:         return Keyboard::Key::F6;
        case VK_F7:         return Keyboard::Key::F7;
        case VK_F8:         return Keyboard::Key::F8;
        case VK_F9:         return Keyboard::Key::F9;
        case VK_F10:        return Keyboard::Key::F10;
        case VK_F11:        return Keyboard::Key::F11;
        case VK_F12:        return Keyboard::Key::F12;
        case VK_F13:        return Keyboard::Key::F13;
        case VK_F14:        return Keyboard::Key::F14;
        case VK_F15:        return Keyboard::Key::F15;
        case VK_F16:        return Keyboard::Key::F16;
        case VK_F17:        return Keyboard::Key::F17;
        case VK_F18:        return Keyboard::Key::F18;
        case VK_F19:        return Keyboard::Key::F19;
        case VK_F20:        return Keyboard::Key::F20;
        case VK_F21:        return Keyboard::Key::F21;
        case VK_F22:        return Keyboard::Key::F22;
        case VK_F23:        return Keyboard::Key::F23;
        case VK_F24:        return Keyboard::Key::F24;

        case VK_NUMPAD0:    return Keyboard::Key::Numpad0;
        case VK_NUMPAD1:    return Keyboard::Key::Numpad1;
        case VK_NUMPAD2:    return Keyboard::Key::Numpad2;
        case VK_NUMPAD3:    return Keyboard::Key::Numpad3;
        case VK_NUMPAD4:    return Keyboard::Key::Numpad4;
        case VK_NUMPAD5:    return Keyboard::Key::Numpad5;
        case VK_NUMPAD6:    return Keyboard::Key::Numpad6;
        case VK_NUMPAD7:    return Keyboard::Key::Numpad7;
        case VK_NUMPAD8:    return Keyboard::Key::Numpad8;
        case VK_NUMPAD9:    return Keyboard::Key::Numpad9;

        case VK_LWIN:       return Keyboard::Key::LSuper;
        case VK_RWIN:       return Keyboard::Key::RSuper;
        case VK_CONTROL:    return ((HIWORD(info) & KF_EXTENDED) == 0) ? Keyboard::Key::LControl
                                                                    : Keyboard::Key::RControl;
        case VK_MENU:       return ((HIWORD(info) & KF_EXTENDED) == 0) ? Keyboard::Key::LAlt
                                                                    : Keyboard::Key::RAlt;
        case VK_SHIFT: {
            static UINT lShiftScanCode = MapVirtualKey(VK_LSHIFT, MAPVK_VK_TO_VSC);
            UINT keyScanCode = (info >> 16) & 0xFF;
            return keyScanCode == lShiftScanCode ? Keyboard::Key::LShift : Keyboard::Key::RShift;
        }

        case VK_LEFT:       return Keyboard::Key::Left;
        case VK_UP:         return Keyboard::Key::Up;
        case VK_RIGHT:      return Keyboard::Key::Right;
        case VK_DOWN:       return Keyboard::Key::Down;

        case VK_PRIOR:      return Keyboard::Key::PageUp;
        case VK_NEXT:       return Keyboard::Key::PageDown;
        case VK_HOME:       return Keyboard::Key::Home;
        case VK_END:        return Keyboard::Key::End;

        case VK_BACK:       return Keyboard::Key::Backspace;
        case VK_DELETE:     return Keyboard::Key::Delete;
        case VK_TAB:        return Keyboard::Key::Tab;
        case VK_RETURN:     return Keyboard::Key::Enter;
        case VK_SPACE:      return Keyboard::Key::Space;
        case VK_ESCAPE:     return Keyboard::Key::Escape;

        case VK_CAPITAL:    return Keyboard::Key::CapsLock;
        case VK_NUMLOCK:    return Keyboard::Key::NumLock;

        case VK_OEM_PLUS:   return Keyboard::Key::Equal;

    
        default:            return Keyboard::Key::Unkown;
    }
}

int Keyboard::keyToWinCode(Key key)
{
    switch (key)
    {
        case Keyboard::Key::A:          return 'A';
        case Keyboard::Key::B:          return 'B';
        case Keyboard::Key::C:          return 'C';
        case Keyboard::Key::D:          return 'D';
        case Keyboard::Key::E:          return 'E';
        case Keyboard::Key::F:          return 'F';
        case Keyboard::Key::G:          return 'G';
        case Keyboard::Key::H:          return 'H';
        case Keyboard::Key::I:          return 'I';
        case Keyboard::Key::J:          return 'J';
        case Keyboard::Key::K:          return 'K';
        case Keyboard::Key::L:          return 'L';
        case Keyboard::Key::M:          return 'M';
        case Keyboard::Key::N:          return 'N';
        case Keyboard::Key::O:          return 'O';
        case Keyboard::Key::P:          return 'P';
        case Keyboard::Key::Q:          return 'Q';
        case Keyboard::Key::R:          return 'R';
        case Keyboard::Key::S:          return 'S';
        case Keyboard::Key::T:          return 'T';
        case Keyboard::Key::U:          return 'U';
        case Keyboard::Key::V:          return 'V';
        case Keyboard::Key::W:          return 'W';
        case Keyboard::Key::X:          return 'X';
        case Keyboard::Key::Y:          return 'Y';
        case Keyboard::Key::Z:          return 'Z';

        case Keyboard::Key::Num0:       return '0';
        case Keyboard::Key::Num1:       return '1';
        case Keyboard::Key::Num2:       return '2';
        case Keyboard::Key::Num3:       return '3';
        case Keyboard::Key::Num4:       return '4';
        case Keyboard::Key::Num5:       return '5';
        case Keyboard::Key::Num6:       return '6';
        case Keyboard::Key::Num7:       return '7';
        case Keyboard::Key::Num8:       return '8';
        case Keyboard::Key::Num9:       return '9';

        case Keyboard::Key::F1:         return VK_F1;
        case Keyboard::Key::F2:         return VK_F2;
        case Keyboard::Key::F3:         return VK_F3;
        case Keyboard::Key::F4:         return VK_F4;
        case Keyboard::Key::F5:         return VK_F5;
        case Keyboard::Key::F6:         return VK_F6;
        case Keyboard::Key::F7:         return VK_F7;
        case Keyboard::Key::F8:         return VK_F8;
        case Keyboard::Key::F9:         return VK_F9;
        case Keyboard::Key::F10:        return VK_F10;
        case Keyboard::Key::F11:        return VK_F11;
        case Keyboard::Key::F12:        return VK_F12;
        case Keyboard::Key::F13:        return VK_F13;
        case Keyboard::Key::F14:        return VK_F14;
        case Keyboard::Key::F15:        return VK_F15;
        case Keyboard::Key::F16:        return VK_F16;
        case Keyboard::Key::F17:        return VK_F17;
        case Keyboard::Key::F18:        return VK_F18;
        case Keyboard::Key::F19:        return VK_F19;
        case Keyboard::Key::F20:        return VK_F20;
        case Keyboard::Key::F21:        return VK_F21;
        case Keyboard::Key::F22:        return VK_F22;
        case Keyboard::Key::F23:        return VK_F23;
        case Keyboard::Key::F24:        return VK_F24;

        case Keyboard::Key::Numpad0:    return VK_NUMPAD0;
        case Keyboard::Key::Numpad1:    return VK_NUMPAD1;
        case Keyboard::Key::Numpad2:    return VK_NUMPAD2;
        case Keyboard::Key::Numpad3:    return VK_NUMPAD3;
        case Keyboard::Key::Numpad4:    return VK_NUMPAD4;
        case Keyboard::Key::Numpad5:    return VK_NUMPAD5;
        case Keyboard::Key::Numpad6:    return VK_NUMPAD6;
        case Keyboard::Key::Numpad7:    return VK_NUMPAD7;
        case Keyboard::Key::Numpad8:    return VK_NUMPAD8;
        case Keyboard::Key::Numpad9:    return VK_NUMPAD9;

        case Keyboard::Key::LSuper:     return VK_LWIN;
        case Keyboard::Key::RSuper:     return VK_RWIN;

        // TODO: Handle control, alt and shift keys with their weird quirks
        case Keyboard::Key::LControl:   return VK_LCONTROL;
        case Keyboard::Key::RControl:   return VK_RCONTROL;
        case Keyboard::Key::LAlt:       return VK_LMENU;
        case Keyboard::Key::RAlt:       return VK_RMENU;
        case Keyboard::Key::LShift:     return VK_LSHIFT;
        case Keyboard::Key::RShift:     return VK_RSHIFT;

        case Keyboard::Key::Left:       return VK_LEFT;
        case Keyboard::Key::Up:         return VK_UP;
        case Keyboard::Key::Right:      return VK_RIGHT;
        case Keyboard::Key::Down:       return VK_DOWN;

        case Keyboard::Key::PageUp:     return VK_PRIOR;
        case Keyboard::Key::PageDown:   return VK_NEXT;
        case Keyboard::Key::Home:       return VK_HOME;
        case Keyboard::Key::End:        return VK_END;

        case Keyboard::Key::Backspace:  return VK_BACK;
        case Keyboard::Key::Delete:     return VK_DELETE;
        case Keyboard::Key::Tab:        return VK_TAB;
        case Keyboard::Key::Enter:      return VK_RETURN;
        case Keyboard::Key::Space:      return VK_SPACE;
        case Keyboard::Key::Escape:     return VK_ESCAPE;

        case Keyboard::Key::CapsLock:   return VK_CAPITAL;
        case Keyboard::Key::NumLock:    return VK_NUMLOCK;

        case Keyboard::Key::Equal:      return VK_OEM_PLUS;

        default: return 0;
    }
}

bool Keyboard::isKeyPressed(Key key)
{
    return (GetAsyncKeyState(Keyboard::keyToWinCode(key)) & 0x8000) != 0;
}

}   // namespace sw
 