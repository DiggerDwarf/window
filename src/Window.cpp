#include <Window.hpp>


Window::Window() :
    m_handle(NULL)
{
}

Window::Window(unsigned x, unsigned y, std::string title) :
    m_handle(NULL)
{
    // If first wiwndow, create Win32 window class
    if (nb_windows == 0)
        createWindowClass();

    // Get global screen context to get info about the screen bounds
    HDC screenContext = GetDC(NULL);
    int left   = (GetDeviceCaps(screenContext, HORZRES) - static_cast<int>(x)) / 2;
    int top    = (GetDeviceCaps(screenContext, VERTRES) - static_cast<int>(y)) / 2;
    int width  = static_cast<int>(x);
    int height = static_cast<int>(y);
    ReleaseDC(NULL, screenContext);

    // Window classic style
    DWORD winStyle = WS_VISIBLE | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

    // register the cursor to set it again later
    this->m_cursor = GetCursor();

    // Set window bounds then let Windows correct them
    RECT rect = {0, 0, width, height};
    AdjustWindowRect(&rect, winStyle, false);
    width  = rect.right - rect.left;
    height = rect.bottom - rect.top;

    // Create the window and pass `this` to be able to reference instance in callbacks
    this->m_handle = CreateWindowA(className, title.c_str(), winStyle, left, top, width, height, NULL, NULL, GetModuleHandle(NULL), this);

    ShowWindow(m_handle, SW_SHOW);

    ++nb_windows;
}

Window::~Window()
{
    if (this->m_handle != NULL)
    {
        DestroyWindow(this->m_handle);
        this->m_handle = NULL;
        --nb_windows;
    }
}

bool Window::getEvent(Event* p_event)
{
    // If the event queue is empty, poll for more
    if (this->m_eventQueue.empty())
    {
        MSG message;
        while (PeekMessageA(&message, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
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

void Window::createWindowClass()
{
    WNDCLASSA windowClass;
    windowClass.style           = 0;                        // i dunno
    windowClass.lpfnWndProc     = &Window::globalCallback;  // window class global callback that handles calling individual callbacks
    windowClass.cbClsExtra      = 0;                        // no extra needed
    windowClass.cbWndExtra      = 0;                        // no extra needed
    windowClass.hInstance       = GetModuleHandle(NULL);    // just get global hInstance
    windowClass.hIcon           = NULL;                     // Set no icon
    windowClass.hCursor         = GetCursor();              // Get default cursor
    windowClass.hbrBackground   = NULL;                     // No default background brush, i clear myself
    windowClass.lpszMenuName    = NULL;                     // No menu cuz idk what it is
    windowClass.lpszClassName   = className;                // Class name
    RegisterClassA(&windowClass);
}

LRESULT CALLBACK Window::globalCallback(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_CREATE)
    {
        // Get window creation arguments
        CREATESTRUCT* createStruct = reinterpret_cast<CREATESTRUCT*>(lParam);

        // Get window pointer that was passed as lpParam to CreateWindow
        Window* windowInstance = reinterpret_cast<Window*>(createStruct->lpCreateParams);

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

    // Call default callback to make sure every message is processed somewhere
    return DefWindowProcA(hWnd, uMsg, wParam, lParam);
}

void Window::processEvent(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (this->m_handle == NULL)
        return;

    Event event;

    switch (uMsg)
    {
        case WM_CLOSE:
        {
            event.type = Event::EventType::WINDOW_CLOSED;
            this->m_eventQueue.push(event);
            break;
        }

        case WM_SETCURSOR:
        {
            if (LOWORD(lParam) == HTCLIENT)
            {
                SetCursor(this->m_cursor);
            }
            
        }

        default:
            break;
    }
}
