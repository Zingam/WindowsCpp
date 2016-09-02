#include <cstdarg>
#include <cstdio>

#include <iostream>

#include <Windows.h>


///////////////////////////////////////////////////////////////////////////////
namespace rme::log
{

int print_log(const char* format, ...)
{
    int result = 0;
    static char stringBuffer[64 * 1024];

    va_list args;
    va_start(args, format);
    result = _vsnprintf_s(stringBuffer, sizeof(stringBuffer), _TRUNCATE, format, args);
    va_end(args);

    OutputDebugStringA(stringBuffer);

    return 0;
}

#define printf(format, ...) \
        print_log(format, __VA_ARGS__)

} // namespace rme::log


///////////////////////////////////////////////////////////////////////////////
#if !defined main_return
#   define main_return(error_code) \
       { \
           system("PAUSE"); \
         \
           return error_code; \
       } 
#endif // !defined main_return(error_code)


///////////////////////////////////////////////////////////////////////////////
int main()
{
    // Prints to Windows console
    std::cout << "Hello console!" << " - std::cout << ..." << "\n";
    fprintf(stderr, "Hello console!%s%s", " - fprintf(stderr, fmt, ...)", "\n");

    // Prints to Visual Studio Debug Output window
    rme::log::printf("Hello console!%s%s", " - log::printf(fmt, ...)", "\n");

    main_return(0);
}
