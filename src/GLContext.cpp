#define SW_WANT_WIN32_SYMBOLS
#define SW_WANT_GL_SYMBOLS
#include <SW/GLContext.hpp>

namespace sw
{

bool GLContext::isGlewInit = false;

namespace
{
    typedef HGLRC (APIENTRY *PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC hDC, HGLRC hShareContext, const int *attribList);
}

GLContext::GLContext() :
    m_deviceContext(NULL),
    m_glHandle(NULL)
{
}

GLContext::~GLContext()
{
    this->close();
}

void GLContext::create(HDC hDc)
{
    // create dummy context
    HGLRC tempContext = wglCreateContext(hDc);

    wglMakeCurrent(hDc, tempContext);
    
    // retrieve wglCreateContextAttribsARB
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wcast-function-type"
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));
    #pragma GCC diagnostic pop

    // parse settings ?
    // Laterrrrrrr

    // create actual context
    this->m_glHandle = wglCreateContextAttribsARB(hDc, NULL, NULL);
    this->set_active();

    if (!GLContext::isGlewInit)
    {
        if (glewInit() != GLEW_OK)
            throw "Failed to initiate glew.\n";
        
        GLContext::isGlewInit = true;
    }
}

void GLContext::close()
{
    if (this->m_glHandle)
    {
        wglDeleteContext(this->m_glHandle);
        this->m_glHandle = NULL;
    }
    this->m_deviceContext = NULL;
}

void GLContext::set_active(bool active)
{
    bool isActive = wglGetCurrentContext() != this->m_glHandle;
    if (active && !isActive) {
        wglMakeCurrent(this->m_deviceContext, this->m_glHandle);
    } else if (!active && isActive) {
        wglMakeCurrent(this->m_deviceContext, NULL);
    }
}

} // namespace sw