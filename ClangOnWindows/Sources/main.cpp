////////////////////////////////////////////////////////////////////////////////
#include <Windows.h>
////////////////////////////////////////////////////////////////////////////////
#include <cstdio>
#include <cstdlib>
#include <iostream>
////////////////////////////////////////////////////////////////////////////////

int
  main (
    [[maybe_unused]] int argc, 
    [[maybe_unused]] char* argv[])
{
    const char* greetClang = "Hello Clang!";
    
    printf      ("libc:   %s\n", greetClang);
    std::cout << "libc++: " << greetClang << "\n";
    
    size_t charCount = 0;
    mbstowcs_s (&charCount, nullptr, 0, greetClang, _TRUNCATE);
    printf ("Chars counted: %zu\n", charCount);
    auto stringBuffer = new wchar_t [charCount];
    auto stringBufferSize = sizeof (wchar_t) * charCount;
    mbstowcs_s (&charCount, stringBuffer, stringBufferSize, greetClang, _TRUNCATE);  
    printf ("Chars converted: %zu\n", charCount);
    MessageBox(nullptr, stringBuffer, L"Windows", MB_ICONWARNING | MB_OK);
    
    delete [] stringBuffer;
    stringBuffer = nullptr;
    
    return 0;
}

