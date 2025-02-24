#ifndef __GLContext_hpp_INCLUDED
#define __GLContext_hpp_INCLUDED


#define VC_EXTRALEAN
#include <windows.h>

#include <GL/glew.h>

namespace sw
{

class GLContext
{
private:
    HDC     m_deviceContext;
    HGLRC   m_glHandle;

    static bool isGlewInit;
public:
    GLContext();
    ~GLContext();

    void create(HDC hDc);
    void close();

    void set_active();
};

} // namespace sw


#endif // __GLContext_hpp_INCLUDED