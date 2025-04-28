#ifndef __Clipboard_hpp_INCLUDED
#define __Clipboard_hpp_INCLUDED

#include <SW/Config.hpp>
#include <SW/Window.hpp>
#include <string>

namespace sw
{

namespace Clipboard
{
    SW_API void set(const std::string& text);
    SW_API std::string get();
}   // namespace Clipboard


}   // namespace sw


#endif // __Clipboard_hpp_INCLUDED