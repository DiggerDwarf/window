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


#endif // __Config_hpp_INCLUDED