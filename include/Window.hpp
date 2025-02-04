#ifndef __Window_hpp_INCLUDED
#define __Window_hpp_INCLUDED

#include <Event.hpp>

#include <windows.h>
#include <string>
#include <queue>

const LPCSTR className = "My_windows_somehow";

inline unsigned nb_windows = 0;


class Window
{
private:
    HWND    m_handle;
    HCURSOR m_cursor;

    std::queue<Event> m_eventQueue;
    static void createWindowClass();
public:
    Window();
    Window(unsigned x, unsigned y, std::string title = "Some window");
    ~Window();

    static LRESULT CALLBACK globalCallback(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    void processEvent(UINT uMsg, WPARAM wParam, LPARAM lParam);

    bool getEvent(Event* p_event);

};


#endif // __Window_hpp_INCLUDED