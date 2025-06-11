#ifndef __Config_hpp_INCLUDED
#define __Config_hpp_INCLUDED


#ifndef SW_STATIC
    #define SW_EXPORT   __declspec(dllexport)
    #define SW_IMPORT   __declspec(dllimport)
#else
    #define SW_EXPORT
    #define SW_IMPORT
#endif

#ifdef SW_BUILD
    #define SW_API SW_EXPORT
#else
    #define SW_API SW_IMPORT
#endif

#ifdef SW_DEBUG
    // If debug mode is enabled, include iostream everywhere for debug printing
    #include <iostream>
#endif

#ifdef SW_WANT_WIN32_SYMBOLS
    #include <windows.h>
#else
    #define DECL_HANDLE(name) struct name##__ ; typedef name##__* name;
    DECL_HANDLE(HWND);
    DECL_HANDLE(HDC);
    DECL_HANDLE(HCURSOR);
    DECL_HANDLE(WINDOWPLACEMENT);
    DECL_HANDLE(HGLRC);
    #define CALLBACK __stdcall
    typedef long long LRESULT, LPARAM;
    typedef unsigned UINT;
    typedef unsigned long long WPARAM;
    typedef const char* LPCSTR;
#endif

#ifdef SW_WANT_GL_SYMBOLS
    #include <GL/glew.h>
#else
    typedef unsigned int GLuint;
    typedef int GLint;
    typedef float GLfloat;
#endif

#endif // __Config_hpp_INCLUDED