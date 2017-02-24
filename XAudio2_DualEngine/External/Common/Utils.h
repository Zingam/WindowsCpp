#pragma once
///////////////////////////////////////////////////////////////////////////////
// System Library inclusions
///////////////////////////////////////////////////////////////////////////////
#include <Unknwn.h>
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Macro definitions
///////////////////////////////////////////////////////////////////////////////
///
/// NAMESPACE_BEGIN
///
#if !defined (NAMESPACE_BEGIN)
#   define NAMESPACE_BEGIN(ns) namespace ns { 
#endif // !defined (NAMESPACE_BEGIN)

///
/// NAMESPACE_END
///
#if !defined (NAMESPACE_END)
#   define NAMESPACE_END(ns) }
#endif // !defined (NAMESPACE_END)

///
/// Main_Return - pauses before returning the error code to Windows
///
#if !defined Main_Return
#   define Main_Return(error_code) \
       { \
           system("PAUSE"); \
         \
           return error_code; \
       } 
#endif // !defined Main_Return(error_code)

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
NAMESPACE_BEGIN(Common::Utils)
///////////////////////////////////////////////////////////////////////////////

///
/// SafeDelete deletes an object and sets the pointer to nullptr
///
template <typename T>
void 
SafeDelete(T*& object)
{
    if (nullptr != object)
    {
        delete object;
        object = nullptr;
    }
}

///
/// SafeDelete deletes an array of objects and sets the pointer to nullptr
///
template <typename T>
void 
SafeDelete_Array(T*& object)
{
    if (nullptr != object)
    {
        delete[] object;
        object = nullptr;
    }
}

///
/// SafeRelease releases a COM interface and sets the pointer to nullptr
///
template <class ComInterface>
void
SafeRelease(ComInterface*& object)
{
    if (nullptr != object)
    {
        object->Release();
        object = nullptr;
    }
}


template <typename XAudio2Voice>
void
SafeDestroyVoice(XAudio2Voice*& object)
{
    if (nullptr != object)
    {
        object->DestroyVoice();
        object = nullptr;
    }
}

///////////////////////////////////////////////////////////////////////////////
NAMESPACE_END(Common::Utils)
///////////////////////////////////////////////////////////////////////////////
