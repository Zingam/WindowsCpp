@echo off

cls

:: Change to a CMake compatible build type: "Debug", "Release", etc.
set "BuildType=Debug"

:: Change to your Visual Studio version
set "VsVersion=Preview\Community"
:: Change to your Visual C++ Toolset version
set "VcVersion=14.12.25827"
:: Chante to your Widows SDK version
set "WinSdkVersion=10.0.16299.0"
:: Change to your target architecture "x86" or "x64"
set "TargetArchitecture=x86"
:: Change to your Clang installation
set "ClangPath=C:\Program Files (x86)\LLVM"

:: Project variables
set "OutputPath=..\__build-output\ClangOnWindows\CMake"

:: Visual C++ paths
set "VsPath=C:\Program Files (x86)\Microsoft Visual Studio\%VsVersion%"
set "VcIncludePath=%VsPath%\VC\Tools\MSVC\%VcVersion%\include"
set "VcLibPath=%VsPath%\VC\Tools\MSVC\%VcVersion%\lib\%TargetArchitecture%"
set "VcToolsetPath=%VsPath%\VC\Tools\MSVC\%VcVersion%\bin\Host%TargetArchitecture%\%TargetArchitecture%"

:: Windows SDK paths
set "WinKitsPath=C:\Program Files (x86)\Windows Kits\10"
set "WinSdkBinPath=%WinKitsPath%\bin\%WinSdkVersion%\%TargetArchitecture%"
set "WinSdkLibPath=%WinKitsPath%\Lib\%WinSdkVersion%"
set "WinSdkIncludePath=%WinKitsPath%\Include\%WinSdkVersion%"

set "WinSdkHeaderIncludePaths=%WinSdkIncludePath%\shared;%WinSdkIncludePath%\ucrt;%WinSdkIncludePath%\um
set "WinSdkLibraryPaths=%WinSdkLibPath%\ucrt\%TargetArchitecture%;%WinSdkLibPath%\um\%TargetArchitecture%"

:: Build tools
set "CMakePath=%VSPath%\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin"
set "NinjaPath=%VSPath%\Common7\IDE\CommonExtensions\Microsoft\CMake\Ninja"

:: Compiler
set "ClangPath=%ClangPath%\msbuild-bin\cl.exe"

:: Convert to backslashes for Ninja
set ClangPath=%ClangPath:\=/%

:: Save original PATH variable so that it can be restored later on
set "OriginalPath=%PATH%"
:: Tool paths
set "PATH=%PATH%;%CMakePath%;%NinjaPath%;%VcToolsetPath%;%WinSdkBinPath%;"
:: Include header paths
set "INCLUDE=%VcIncludePath%;%WinSdkHeaderIncludePaths%;"
:: Library paths
set "LIB=%VcLibPath%;%WinSdkLibraryPaths%;"

:: Create the output directory
if exist %OutputPath% (
  if not exist %OutputPath%\CMakeCache.txt (
    echo "Deleting: %OutputPath%"
    rmdir /q /s %OutputPath%
    mkdir %OutputPath%
  )
) else (
  mkdir %OutputPath%
)

if "%TargetArchitecture%" == "x86" (
  set "ClangFlags=-m32"
) else if "%TargetArchitecture%" == "x64" (
  set "ClangFlags=-m64"
) else (
  echo Invalid target architecture: "%TargetArchitecture%". Supported architectures are "x86" and "x64".
  exit /b
)

set "CMakeFlags=-DCMAKE_BUILD_TYPE=%BuildType%"
set "CMakeFlags=%CMakeFlags% -DCMAKE_C_COMPILER="%ClangPath%""
set "CMakeFlags=%CMakeFlags% -DCMAKE_C_FLAGS="%ClangFlags%""
set "CMakeFlags=%CMakeFlags% -DCMAKE_CXX_COMPILER="%ClangPath%""
set "CMakeFlags=%CMakeFlags% -DCMAKE_CXX_FLAGS="%ClangFlags%""

pushd %OutputPath%
echo     Generating the project in: %~dp0
"%CMakePath%\CMake.exe" %CMakeFlags% -G Ninja "%~dp0"
echo     Building the project...
"%NinjaPath%\Ninja.exe"
"%NinjaPath%\Ninja.exe" install
popd

set "PATH=%OriginalPath%"
