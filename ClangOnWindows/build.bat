@echo off

cls

:: Change to your LLVM installation
set "LLVMPath=C:\Program Files\LLVM"
:: Change to your Visual Studio 2017 installation
set "VSPath=C:\Program Files (x86)\Microsoft Visual Studio\Preview\Community"
set "VSIDE=%VSPath%\Common7\IDE"
set "VSVersion=14.12.25827"
:: Change to your Windows Kit version & installation
set "WinSDKVersion=10.0.16299.0"
set "WinSDKPath=C:\Program Files (x86)\Windows Kits\10"

:: Change this to your resulting exe
set "ExecutableName=ClangOnWindows"

:: Project variables
set "OutputPath=..\__build_output"
set "IntDirPath=%OutputPath%\IntDir"
set "OutputExe=%OutputPath%\%ExecutableName%.exe"

:: Create the output directory
if exist %OutputPath% (
    echo "Deleting: %OutputPath%"
    rmdir /q /s %OutputPath%
)
mkdir %IntDirPath%

:: Setup
set "VSBasePath=%VSPath%\VC\Tools\MSVC\%VSVersion%"
set "PATH=%PATH%;%LLVMPath%\bin;%VSBasePath%\bin\HostX64\x64"

:: Compiler Flags
set CPPFLAGS= ^
 -std=c++2a -Wall -Wextra -m64 -g

:: Fix linker warnings: LNK4217
set CPPFLAGS=%CPPFLAGS% ^
 -Xclang -flto-visibility-public-std
 
:: Defines
set CPPDEFINES= ^
 -D_UNICODE ^
 -DUNICODE

set CPPINCLUDES= ^
  -I "%VSBasePath%\include" ^
  -I "%WinSDKPath%\Include\%WinSDKVersion%\shared" ^
  -I "%WinSDKPath%\Include\%WinSDKVersion%\ucrt" ^
  -I "%WinSDKPath%\Include\%WinSDKVersion%\um"

echo "Compiling: %OutputExe%"
:: Compiling
for /r %Sources% %%f in (*.cpp) do (
    @clang++.exe "%%~f" -o "%IntDirPath%\%%~nf.o" -c %CPPFLAGS% %CPPDEFINES%
)

:: Linking
set "LINK_FILES="
for /r %IntDirPath% %%f in (*.o) do (
    set "LINK_FILES=%LINK_FILES% %%~f"
)

echo "Linking %OutputExe%"
:: MSVC linker
set LDFLAGS_LINK= ^
 /NOLOGO ^
 /SUBSYSTEM:CONSOLE ^
 /DEBUG

set LDLIBS_LINK= ^
 /LIBPATH:"%VSBasePath%\lib\x64" ^
 /LIBPATH:"%WinSDKPath%\Lib\%WinSDKVersion%\ucrt\x64" ^
 /LIBPATH:"%WinSDKPath%\Lib\%WinSDKVersion%\um\x64" ^
 libucrt.lib libvcruntime.lib libcmt.lib libcpmt.lib ^
 legacy_stdio_definitions.lib oldnames.lib ^
 legacy_stdio_wide_specifiers.lib ^
 kernel32.lib User32.lib
 
link.exe %LINK_FILES% /OUT:"%OutputExe%" %LDFLAGS_LINK% %LDLIBS_LINK%

echo "Done!"

:: Open a Command prompt in the build output directory
start cmd.exe /K "cd /d "%OutputPath%" & echo "Type ClangOnWindows.exe" & set PATH=%PATH%;%VSIDE%"

:: LLD Linker Libs
set LDFLAGS= ^
 -nodefaultlib ^
 -machine:x64 ^
 -subsystem:console

set LDLIBS= ^
 -libpath:"%VSBasePath%\lib\x64" ^
 -libpath:"%WinSDKPath%\Lib\%WinSDKVersion%\ucrt\x64" ^
 -libpath:"%WinSDKPath%\Lib\%WinSDKVersion%\um\x64" ^
 libucrt.lib libvcruntime.lib libcmt.lib libcpmt.lib ^
 legacy_stdio_definitions.lib oldnames.lib ^
 legacy_stdio_wide_specifiers.lib ^
 kernel32.lib User32.lib
 
::lld-link.exe %LINK_FILES% -out:"%OutputExe%" %LDFLAGS% %LDLIBS%
