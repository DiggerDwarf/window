#include <Window.hpp>

#include <iostream>

namespace sw
{

// Done, don't touch unless class parameters need to be changed
void Window::createWindowClass()
{
    WNDCLASSA windowClass;
    windowClass.style           = CS_OWNDC;                        // i dunno
    windowClass.lpfnWndProc     = &Window::globalCallback;  // window class global callback that handles calling individual callbacks
    windowClass.cbClsExtra      = 0;                        // no extra needed
    windowClass.cbWndExtra      = 0;                        // no extra needed
    windowClass.hInstance       = GetModuleHandle(NULL);    // just get global hInstance
    windowClass.hIcon           = NULL;                     // Set no icon
    windowClass.hCursor         = NULL;                     // Get no cursor
    windowClass.hbrBackground   = NULL;                     // No default background brush, i clear myself
    windowClass.lpszMenuName    = NULL;                     // No menu cuz idk what it is
    windowClass.lpszClassName   = Window::className;        // Class name
    RegisterClassA(&windowClass);
}

Keyboard::Key Window::translateKeyCode(WPARAM key, LPARAM info)
{
    // TODO: maybe order them in order of `key` to match documentation page ?
    switch (key)
    {
        case 'A': return Keyboard::Key::A;
        case 'B': return Keyboard::Key::B;
        case 'C': return Keyboard::Key::C;
        case 'D': return Keyboard::Key::D;
        case 'E': return Keyboard::Key::E;
        case 'F': return Keyboard::Key::F;
        case 'G': return Keyboard::Key::G;
        case 'H': return Keyboard::Key::H;
        case 'I': return Keyboard::Key::I;
        case 'J': return Keyboard::Key::J;
        case 'K': return Keyboard::Key::K;
        case 'L': return Keyboard::Key::L;
        case 'M': return Keyboard::Key::M;
        case 'N': return Keyboard::Key::N;
        case 'O': return Keyboard::Key::O;
        case 'P': return Keyboard::Key::P;
        case 'Q': return Keyboard::Key::Q;
        case 'R': return Keyboard::Key::R;
        case 'S': return Keyboard::Key::S;
        case 'T': return Keyboard::Key::T;
        case 'U': return Keyboard::Key::U;
        case 'V': return Keyboard::Key::V;
        case 'W': return Keyboard::Key::W;
        case 'X': return Keyboard::Key::X;
        case 'Y': return Keyboard::Key::Y;
        case 'Z': return Keyboard::Key::Z;

        case '0': return Keyboard::Key::Num0;
        case '1': return Keyboard::Key::Num1;
        case '2': return Keyboard::Key::Num2;
        case '3': return Keyboard::Key::Num3;
        case '4': return Keyboard::Key::Num4;
        case '5': return Keyboard::Key::Num5;
        case '6': return Keyboard::Key::Num6;
        case '7': return Keyboard::Key::Num7;
        case '8': return Keyboard::Key::Num8;
        case '9': return Keyboard::Key::Num9;

        case VK_F1:  return Keyboard::Key::F1;
        case VK_F2:  return Keyboard::Key::F2;
        case VK_F3:  return Keyboard::Key::F3;
        case VK_F4:  return Keyboard::Key::F4;
        case VK_F5:  return Keyboard::Key::F5;
        case VK_F6:  return Keyboard::Key::F6;
        case VK_F7:  return Keyboard::Key::F7;
        case VK_F8:  return Keyboard::Key::F8;
        case VK_F9:  return Keyboard::Key::F9;
        case VK_F10: return Keyboard::Key::F10;
        case VK_F11: return Keyboard::Key::F11;
        case VK_F12: return Keyboard::Key::F12;
        case VK_F13: return Keyboard::Key::F13;
        case VK_F14: return Keyboard::Key::F14;
        case VK_F15: return Keyboard::Key::F15;
        case VK_F16: return Keyboard::Key::F16;
        case VK_F17: return Keyboard::Key::F17;
        case VK_F18: return Keyboard::Key::F18;
        case VK_F19: return Keyboard::Key::F19;
        case VK_F20: return Keyboard::Key::F20;
        case VK_F21: return Keyboard::Key::F21;
        case VK_F22: return Keyboard::Key::F22;
        case VK_F23: return Keyboard::Key::F23;
        case VK_F24: return Keyboard::Key::F24;

        case VK_NUMPAD0: return Keyboard::Key::Numpad0;
        case VK_NUMPAD1: return Keyboard::Key::Numpad1;
        case VK_NUMPAD2: return Keyboard::Key::Numpad2;
        case VK_NUMPAD3: return Keyboard::Key::Numpad3;
        case VK_NUMPAD4: return Keyboard::Key::Numpad4;
        case VK_NUMPAD5: return Keyboard::Key::Numpad5;
        case VK_NUMPAD6: return Keyboard::Key::Numpad6;
        case VK_NUMPAD7: return Keyboard::Key::Numpad7;
        case VK_NUMPAD8: return Keyboard::Key::Numpad8;
        case VK_NUMPAD9: return Keyboard::Key::Numpad9;

        case VK_LWIN:    return Keyboard::Key::LSuper;
        case VK_RWIN:    return Keyboard::Key::RSuper;
        case VK_CONTROL: return ((HIWORD(info) & KF_EXTENDED) == 0) ? Keyboard::Key::LControl
                                                                    : Keyboard::Key::RControl;
        case VK_MENU:    return ((HIWORD(info) & KF_EXTENDED) == 0) ? Keyboard::Key::LAlt
                                                                    : Keyboard::Key::RAlt;
        case VK_SHIFT: {
            static UINT lShiftScanCode = MapVirtualKey(VK_LSHIFT, MAPVK_VK_TO_VSC);
            UINT keyScanCode = (info >> 16) & 0xFF;
            return keyScanCode == lShiftScanCode ? Keyboard::Key::LShift : Keyboard::Key::RShift;
        }

        case VK_LEFT:   return Keyboard::Key::Left;
        case VK_UP:     return Keyboard::Key::Up;
        case VK_RIGHT:  return Keyboard::Key::Right;
        case VK_DOWN:   return Keyboard::Key::Down;

        case VK_PRIOR:  return Keyboard::Key::PageUp;
        case VK_NEXT:   return Keyboard::Key::PageDown;
        case VK_HOME:   return Keyboard::Key::Home;
        case VK_END:    return Keyboard::Key::End;

        case VK_BACK:   return Keyboard::Key::Backspace;
        case VK_DELETE: return Keyboard::Key::Delete;
        case VK_TAB:    return Keyboard::Key::Tab;
        case VK_RETURN: return Keyboard::Key::Enter;
        case VK_SPACE:  return Keyboard::Key::Space;
        case VK_ESCAPE: return Keyboard::Key::Escape;

        case VK_CAPITAL:    return Keyboard::Key::CapsLock;
        case VK_NUMLOCK:    return Keyboard::Key::NumLock;

        case VK_OEM_PLUS:   return Keyboard::Key::Equal;

    
        default: return Keyboard::Key::Unkown;
    }
}

WINDOWPLACEMENT Window::getWindowPlacementInfo() const
{
    WINDOWPLACEMENT out;
    out.length = sizeof(WINDOWPLACEMENT);
    GetWindowPlacement(this->m_handle, &out);
    return out;
}

// Done
Window::Window() :
    m_handle(NULL),
    m_usedCursor(Window::cursor_arrow)
{
}

// Done until it isn't
// If I implement more stuff, it'll probably need more initializing
Window::Window(unsigned x, unsigned y, std::string title, float targetFPS) :
    m_handle(NULL),
    m_usedCursor(Window::cursor_arrow),
    m_targetRate(Time::fromSeconds(1.0F/targetFPS))
{
    // If first wiwndow, create Win32 window class
    if (nb_windows == 0)
    {
        createWindowClass();
        HDC screenContext = GetDC(NULL);
        Window::screenSize = iVec2(
            GetDeviceCaps(screenContext, HORZRES),
            GetDeviceCaps(screenContext, VERTRES)
        );
    }

    // Get global screen context to get info about the screen bounds
    HDC screenContext = GetDC(NULL);
    int left   = (GetDeviceCaps(screenContext, HORZRES) - static_cast<int>(x)) / 2;
    int top    = (GetDeviceCaps(screenContext, VERTRES) - static_cast<int>(y)) / 2;
    int width  = static_cast<int>(x);
    int height = static_cast<int>(y);
    ReleaseDC(NULL, screenContext);

    // Window classic style
    DWORD winStyle = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_THICKFRAME | WS_MAXIMIZEBOX;


    // Set window bounds then let Windows correct them
    RECT rect = {0, 0, width, height};
    // AdjustWindowRect(&rect, winStyle, false);
    width  = rect.right - rect.left;
    height = rect.bottom - rect.top;

    // Create the window and pass `this` to be able to reference instance in callbacks
    this->m_handle = CreateWindowA(Window::className, title.c_str(), winStyle, left, top, width, height, NULL, NULL, GetModuleHandle(NULL), this);
    // Can cache device context because of window class style CS_OWNDC
    this->m_deviceContext = GetDC(this->m_handle);

    ++nb_windows;


    PIXELFORMATDESCRIPTOR pfd = {0};
    pfd.nSize              = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion           = 1;
    pfd.dwFlags            = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType         = PFD_TYPE_RGBA;
    pfd.cColorBits         = 32;
    pfd.cDepthBits         = 24;
    pfd.cStencilBits       = 8;

    int pixelFormatNumber = ChoosePixelFormat(this->m_deviceContext, &pfd);
    SetPixelFormat(this->m_deviceContext, pixelFormatNumber, &pfd);

    this->m_glContext.create(this->m_deviceContext);

    ShowWindow(this->m_handle, SW_SHOW);


    // this->m_OpenGL_Handle = wglCreateContext(this->m_deviceContext);

    
    // if (!this->m_OpenGL_Handle)
    // {
    //     std::cout << "fuck this shit\n";
    // }
    this->m_internalClock.restart();
}

// Should be done, maybe add more cleanup if I find out it's needed
Window::~Window()
{
    // ignore unopened windows
    if (this->m_handle == NULL) return;

    DestroyWindow(this->m_handle);
    this->m_handle = NULL;
    --nb_windows;

    // If it's the last window, the program is probably ending so we unregister the window class
    if (nb_windows == 0)
        UnregisterClassA(Window::className, GetModuleHandleA(NULL));
}

// Mostly finished
// TODO : maybe prevent certain events from reaching DefWindowProc
LRESULT CALLBACK Window::globalCallback(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_CREATE)
    {
        // Get window creation arguments
        const CREATESTRUCT* createStruct = reinterpret_cast<CREATESTRUCT*>(lParam);

        // Get window pointer that was passed as lpParam to CreateWindow
        const Window* windowInstance = reinterpret_cast<Window*>(createStruct->lpCreateParams);

        // Set this Window instance pointer as user data in the window data
        SetWindowLongPtrA(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(windowInstance));
    }

    // if callback is associated to a handle, retrieve the Window instance pointer
    Window* windowInstance = (hWnd != NULL) ? reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA)) : NULL;

    // If it's a valid pointer
    if (windowInstance != NULL)
    {
        windowInstance->processEvent(uMsg, wParam, lParam);
    }
    
    if (uMsg == WM_CLOSE)
        return 0;

    if (uMsg == WM_SYSCOMMAND && wParam == SC_KEYMENU)
        return 0;

    // Call default callback to make sure every message is processed somewhere
    return DefWindowProcA(hWnd, uMsg, wParam, lParam);
}

// Highly unfinished
// TODO : process more event types
// Follow the pattern and continue the switch
void Window::processEvent(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // Ignore if window has no handle
    if (this->m_handle == NULL)
        return;
    
    // Get an event ready to be set and sent away
    Event event;

    switch (uMsg)
    {
        // Called when clicking on the window's close button
        case WM_CLOSE:
        {
            event.type = Event::EventType::Close;
            this->m_eventQueue.push(event);
            break;
        }

        // Called every time the cursor moves and is in the window
        case WM_SETCURSOR:
        {
            if (LOWORD(lParam) == HTCLIENT)
                SetCursor(this->m_usedCursor);
            break;
        }
        
        case WM_SYSKEYDOWN:
        case WM_KEYDOWN:
        {
            event.type = Event::EventType::KeyPress;
            event.keyInfo.key = Window::translateKeyCode(wParam, lParam);
            this->m_eventQueue.push(event);
            break;
        }
        
        case WM_SYSKEYUP:
        case WM_KEYUP:
        {
            event.type = Event::EventType::KeyRelease;
            event.keyInfo.key = Window::translateKeyCode(wParam, lParam);
            this->m_eventQueue.push(event);
            break;
        }

        case WM_LBUTTONDOWN:
        {
            event.type = Event::EventType::MousePress;
            event.mouseInfo.button = Mouse::Button::Left;
            event.mouseInfo.x = LOWORD(lParam);
            event.mouseInfo.y = HIWORD(lParam);
            this->m_eventQueue.push(event);
            break;
        }

        case WM_MBUTTONDOWN:
        {
            event.type = Event::EventType::MousePress;
            event.mouseInfo.button = Mouse::Button::Middle;
            event.mouseInfo.x = LOWORD(lParam);
            event.mouseInfo.y = HIWORD(lParam);
            this->m_eventQueue.push(event);
            break;
        }

        case WM_RBUTTONDOWN:
        {
            event.type = Event::EventType::MousePress;
            event.mouseInfo.button = Mouse::Button::Right;
            event.mouseInfo.x = LOWORD(lParam);
            event.mouseInfo.y = HIWORD(lParam);
            this->m_eventQueue.push(event);
            break;
        }

        case WM_XBUTTONDOWN:
        {
            event.type = Event::EventType::MousePress;
            event.mouseInfo.button = (HIWORD(wParam) == XBUTTON1) ? Mouse::Button::Extra1 : Mouse::Button::Extra2;
            event.mouseInfo.x = LOWORD(lParam);
            event.mouseInfo.y = HIWORD(lParam);
            this->m_eventQueue.push(event);
            break;
        }

        case WM_LBUTTONUP:
        {
            event.type = Event::EventType::MouseRelease;
            event.mouseInfo.button = Mouse::Button::Left;
            event.mouseInfo.x = LOWORD(lParam);
            event.mouseInfo.y = HIWORD(lParam);
            this->m_eventQueue.push(event);
            break;
        }

        case WM_MBUTTONUP:
        {
            event.type = Event::EventType::MouseRelease;
            event.mouseInfo.button = Mouse::Button::Middle;
            event.mouseInfo.x = LOWORD(lParam);
            event.mouseInfo.y = HIWORD(lParam);
            this->m_eventQueue.push(event);
            break;
        }

        case WM_RBUTTONUP:
        {
            event.type = Event::EventType::MouseRelease;
            event.mouseInfo.button = Mouse::Button::Right;
            event.mouseInfo.x = LOWORD(lParam);
            event.mouseInfo.y = HIWORD(lParam);
            this->m_eventQueue.push(event);
            break;
        }

        case WM_XBUTTONUP:
        {
            event.type = Event::EventType::MouseRelease;
            event.mouseInfo.button = (HIWORD(wParam) == XBUTTON1) ? Mouse::Button::Extra1 : Mouse::Button::Extra2;
            event.mouseInfo.x = LOWORD(lParam);
            event.mouseInfo.y = HIWORD(lParam);
            this->m_eventQueue.push(event);
            break;
        }

        // Unprocessed events
        default:
            break;
    }
}

void Window::update()
{
    // Update
    SwapBuffers(this->m_deviceContext);
    
    const Time deltaTime = this->m_internalClock.restart();

    const long long diff = this->m_targetRate.asMicroseconds() - deltaTime.asMicroseconds();

    if (diff >= 0)
        Sleep(diff/1000);
    
}

void Window::clear(const Color& clearColor)
{
    this->m_glContext.set_active();
    glClearColor(
        clearColor.r / 255.F,
        clearColor.g / 255.F,
        clearColor.b / 255.F,
        clearColor.a / 255.F
    );
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::setTargetFPS(float targetFPS)
{
    this->m_targetRate = Time::fromSeconds(1.0F/targetFPS);
}

// Should be done as it gives all the work to oter functions
bool Window::getEvent(Event* p_event)
{
    // If the event queue is empty, poll for more
    if (this->m_eventQueue.empty())
    {
        // Gather all the available messages
        MSG message;
        while (PeekMessageA(&message, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            // Send the messages to the callback function
            DispatchMessageA(&message);
        }
        
    }

    // If there is events in the queue, write on event and return true
    if (!this->m_eventQueue.empty())
    {
        *p_event = this->m_eventQueue.front();
        this->m_eventQueue.pop();
        return true;
    }
    return false;
}

// Easy and done, update when adding cursors to Mouse::Cursors
void Window::setCursor(Mouse::Cursor cursorType)
{
    switch (cursorType)
    {
        case Mouse::Cursor::ARROW:
            this->m_usedCursor = Window::cursor_arrow;
            break;
        case Mouse::Cursor::FINGER:
            this->m_usedCursor = Window::cursor_finger;
            break;
        case Mouse::Cursor::CROSS:
            this->m_usedCursor = Window::cursor_cross;
            break;
        case Mouse::Cursor::NO:
            this->m_usedCursor = Window::cursor_no;
            break;
        default:
            break;
    }
}

// Straightforward and done
const HWND Window::getWin32Handle() const
{
    return this->m_handle;
}

iVec2 Window::getPosition() const
{
    WINDOWPLACEMENT info = this->getWindowPlacementInfo();
    return iVec2(info.rcNormalPosition.left, info.rcNormalPosition.top);
}

iVec2 Window::getSize() const
{
    WINDOWPLACEMENT info = this->getWindowPlacementInfo();
    return iVec2(
        info.rcNormalPosition.right - info.rcNormalPosition.left,
        info.rcNormalPosition.bottom - info.rcNormalPosition.top
    );
}

void Window::setPosition(iVec2 newPosition)
{
    WINDOWPLACEMENT info = this->getWindowPlacementInfo();
    info.rcNormalPosition.right  += newPosition.x - info.rcNormalPosition.left;
    info.rcNormalPosition.bottom += newPosition.y - info.rcNormalPosition.top;
    info.rcNormalPosition.left    = newPosition.x;
    info.rcNormalPosition.top     = newPosition.y;
    SetWindowPlacement(this->m_handle, &info);
}

void Window::move(fVec2 offset)
{
    fVec2 totalOffset = offset + this->m_subPixel;
    iVec2 actualOffset(totalOffset);
    this->m_subPixel = totalOffset - fVec2(actualOffset);

    WINDOWPLACEMENT info = this->getWindowPlacementInfo();
    info.rcNormalPosition.right  += actualOffset.x;
    info.rcNormalPosition.left   += actualOffset.x;
    info.rcNormalPosition.top    += actualOffset.y;
    info.rcNormalPosition.bottom += actualOffset.y;
    SetWindowPlacement(this->m_handle, &info);
}

void Window::setSize(iVec2 newSize)
{
    WINDOWPLACEMENT info = this->getWindowPlacementInfo();
    info.rcNormalPosition.right = info.rcNormalPosition.left + newSize.x;
    info.rcNormalPosition.bottom = info.rcNormalPosition.top + newSize.y;
    SetWindowPlacement(this->m_handle, &info);
}

void Window::setBox(iVec2 topLeft, iVec2 bottomRight)
{
    WINDOWPLACEMENT info = this->getWindowPlacementInfo();
    info.rcNormalPosition.left   = topLeft.x;
    info.rcNormalPosition.top    = topLeft.y;
    info.rcNormalPosition.right  = bottomRight.x;
    info.rcNormalPosition.bottom = bottomRight.y;
    SetWindowPlacement(this->m_handle, &info);
}

iVec2 Window::screenToWindow(const iVec2 pos) const
{
    iVec2 out = pos;
    ScreenToClient(this->m_handle, reinterpret_cast<LPPOINT>(&out));
    return out;
}

iVec2 Window::windowToScreen(const iVec2 pos) const
{
    iVec2 out = pos;
    ClientToScreen(this->m_handle, reinterpret_cast<LPPOINT>(&out));
    return out;
}

const iVec2 &Window::getScreenSize()
{
    return Window::screenSize;
}

}   // namespace sw

