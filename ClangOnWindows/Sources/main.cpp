////////////////////////////////////////////////////////////////////////////////
#include <Windows.h>
////////////////////////////////////////////////////////////////////////////////
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>
////////////////////////////////////////////////////////////////////////////////

int
  main (
    [[maybe_unused]] int argc, 
    [[maybe_unused]] char* argv [])
{
    const char* greetClang = "Hello Clang!";
    
    printf      ("libc:   %s\n", greetClang);
    std::cout << "libc++: " << greetClang << "\n";
    
    size_t charCount = 0;
    mbstowcs_s (&charCount, nullptr, 0, greetClang, _TRUNCATE);
    // Don't count the terminating "\0"
    --charCount;
    printf ("Chars counted: %zu\n", charCount);
    auto stringBuffer = std::make_unique<wchar_t []> (charCount + 1);
    auto stringBufferSize = sizeof (wchar_t) * charCount;
    mbstowcs_s (&charCount, stringBuffer.get (), charCount, greetClang, _TRUNCATE);
    printf ("Chars converted: %zu\n", charCount);

    MessageBox(nullptr, stringBuffer.get (), L"Windows", MB_ICONWARNING | MB_OK);
    
    return 0;
}

