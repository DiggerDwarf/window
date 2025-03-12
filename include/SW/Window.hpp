#ifndef __Window_hpp_INCLUDED
#define __Window_hpp_INCLUDED

#include <SW/Config.hpp>

#define VC_EXTRALEAN

#include <SW/Event.hpp>
#include <SW/Vector.hpp>
#include <SW/Mouse.hpp>
#include <SW/Keyboard.hpp>
#include <SW/GLContext.hpp>
#include <SW/Clock.hpp>
#include <SW/Color.hpp>
#include <SW/View.hpp>

#include <winuser.h>
#include <string>
#include <queue>
#include <map>


namespace sw
{

class SW_API Window
{
private:
    HWND            m_handle;
    HDC             m_deviceContext;
    GLContext       m_glContext;
    HCURSOR&        m_usedCursor;
    fVec2           m_subPixel;         // This is needed to move the window with float values
    Clock           m_internalClock;    // This is needed to manage the frame rate
    Time            m_targetRate;

    static unsigned nb_windows;

    static iVec2 screenSize;

    std::queue<Event> m_eventQueue;
    static void createWindowClass();
    inline static const LPCSTR className = "My_windows_somehow";

    static HCURSOR cursor_arrow;
    static HCURSOR cursor_finger;
    static HCURSOR cursor_cross;
    static HCURSOR cursor_no;

    WINDOWPLACEMENT getWindowPlacementInfo() const;

public:
    Window(unsigned x, unsigned y, std::string title, float targetFPS = 60);
    ~Window();
    
    Window(const Window& other) = delete;
    Window& operator=(const Window& other) = delete;

    // void open(unsigned x, unsigned y, std::string title = "Some window");
    // void close();

    static LRESULT CALLBACK globalCallback(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    void processEvent(UINT uMsg, WPARAM wParam, LPARAM lParam);

    void display();
    void clear(const Color& clearColor = Color::Black);
    void setTargetFPS(float targetFPS);

    bool getEvent(Event* p_event);

    void setCursor(Mouse::Cursor cursorType);

    const HWND getWin32Handle() const;
    const HDC getDeviceContext() const;

    iVec2 getPosition() const;
    iVec2 getSize() const;
    void setPosition(iVec2 newPosition);
    void move(fVec2 offset);
    void setSize(iVec2 newSize);
    void setBox(iVec2 topLeft, iVec2 bottomRight);

    iVec2 screenToWindow(const iVec2& pos) const;
    iVec2 windowToScreen(const iVec2& pos) const;

    static const iVec2& getScreenSize();

    void setView(const View& view);
};  // class Window

}   // namespace sw


#endif // __Window_hpp_INCLUDED