#ifndef __Window_hpp_INCLUDED
#define __Window_hpp_INCLUDED

#define VC_EXTRALEAN
#include <Event.hpp>
#include <Vector.hpp>
#include <Mouse.hpp>
#include <Keyboard.hpp>

#include <winuser.h>
#include <string>
#include <queue>
#include <map>


inline unsigned nb_windows = 0;


class Window
{
private:
    HWND            m_handle;
    HCURSOR&        m_usedCursor;
    fVec2           m_subPixel;
    inline static iVec2 screenSize = iVec2();

    std::queue<Event> m_eventQueue;
    static void createWindowClass();
    inline static const LPCSTR className = "My_windows_somehow";

    inline static HCURSOR cursor_arrow = LoadCursor(NULL, IDC_ARROW);
    inline static HCURSOR cursor_finger = LoadCursor(NULL, IDC_HAND);
    inline static HCURSOR cursor_cross = LoadCursor(NULL, IDC_CROSS);
    inline static HCURSOR cursor_no = LoadCursor(NULL, IDC_NO);

    static Keyboard::Key translateKeyCode(WPARAM key, LPARAM info);

    WINDOWPLACEMENT getWindowPlacementInfo() const;

public:

    Window();
    Window(unsigned x, unsigned y, std::string title = "Some window");
    ~Window();

    // void open(unsigned x, unsigned y, std::string title = "Some window");
    // void close();

    static LRESULT CALLBACK globalCallback(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    void processEvent(UINT uMsg, WPARAM wParam, LPARAM lParam);

    bool getEvent(Event* p_event);

    void setCursor(Mouse::Cursor cursorType);

    const HWND getWin32Handle() const;

    iVec2 getPosition() const;
    iVec2 getSize() const;
    void setPosition(iVec2 newPosition);
    void move(fVec2 offset);
    void setSize(iVec2 newSize);
    void setBox(iVec2 topLeft, iVec2 bottomRight);

    iVec2 screenToWindow(const iVec2 pos) const;
    iVec2 windowToScreen(const iVec2 pos) const;

    static const iVec2& getScreenSize();
};


#endif // __Window_hpp_INCLUDED