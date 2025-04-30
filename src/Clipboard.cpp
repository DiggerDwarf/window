#define SW_WANT_WIN32_SYMBOLS
#include <SW/Clipboard.hpp>


namespace sw
{

void Clipboard::set(const std::string& text)
{
    if (!OpenClipboard(NULL))
    {
        #ifdef SW_DEBUG
            std::cerr << "Failed to open clipboard\n";
            std::cerr << "Windows gave error code : " << GetLastError() << '\n';
        #endif
        return;
    }

    if (!EmptyClipboard())
    {
        #ifdef SW_DEBUG
            std::cerr << "Failed to empty the clipboard";
            std::cerr << "Windows gave error code : " << GetLastError() << '\n';
        #endif
        CloseClipboard();
        return;
    }

    HANDLE cstr_handle = GlobalAlloc(GHND, text.size() + 1);

    if (!cstr_handle)
    {
        #ifdef SW_DEBUG
            std::cerr << "Failed to allocate space for clipboard content\n";
            std::cerr << "Windows gave error code : " << GetLastError() << '\n';
        #endif
        CloseClipboard();
        return;
    }

    char* cstr = static_cast<char*>(GlobalLock(cstr_handle));
    memcpy(cstr, text.data(), text.size());
    GlobalUnlock(cstr_handle);

    if (!SetClipboardData(CF_TEXT, cstr_handle))
    {
        #ifdef SW_DEBUG
            std::cerr << "Failed to set clipboard contents\n";
            std::cerr << "Windows gave error code : " << GetLastError() << '\n';
        #endif
    }
    CloseClipboard();
}

std::string Clipboard::get()
{
    std::string clipboardText;

    if (!IsClipboardFormatAvailable(CF_TEXT))
    {
        #ifdef SW_DEBUG
            std::cerr << "Failed to get clipboard data in text format\n";
            std::cerr << "Windows gave error code : " << GetLastError() << '\n';
        #endif
        return clipboardText;
    }

    if (!OpenClipboard(NULL))
    {
        #ifdef SW_DEBUG
            std::cerr << "Failed to open clipboard\n";
            std::cerr << "Windows gave error code : " << GetLastError() << '\n';
        #endif
        return clipboardText;
    }

    HANDLE clipDataHandle = GetClipboardData(CF_TEXT);

    if (!clipDataHandle)
    {
        #ifdef SW_DEBUG
            std::cerr << "Failed to retrieve clipboard contents\n";
            std::cerr << "Windows gave error code : " << GetLastError() << '\n';
        #endif
        CloseClipboard();
        return clipboardText;
    }

    const char* clip_cstr = static_cast<char*>(GlobalLock(clipDataHandle));
    clipboardText.assign(clip_cstr);
    GlobalUnlock(clipDataHandle);

    CloseClipboard();

    return clipboardText;
}

}   // namespace sw
