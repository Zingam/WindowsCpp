#pragma once

////////////////////////////////////////////////////////////////////////////////
// REngine Base
////////////////////////////////////////////////////////////////////////////////
#if !defined (NAMESPACE_BEGIN)
#   define NAMESPACE_BEGIN(ns) namespace ns {
#endif
#if !defined (NAMESPACE_END)
#   define NAMESPACE_END(ns) }
#endif
////////////////////////////////////////////////////////////////////////////////
// System headers
////////////////////////////////////////////////////////////////////////////////
#include <Windows.h>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_BEGIN (REngine::Core::Windows)
////////////////////////////////////////////////////////////////////////////////

template <typename I>
class ComPtr
{
  // Hide virtual functions
  template <typename I_>
  struct ComPtr_ : public I_
  {
    // ERROR: Use of member function 'unsigned long __stdcall AddRef ()' is
    // disallowed.
    template <typename M = bool>
    auto __stdcall AddRef () -> unsigned long;
    // ERROR: Use of member function 'unsigned long __stdcall Release ()' is
    // disallowed.
    template <typename M = bool>
    auto __stdcall Release () -> unsigned long;
  };

 public:
  ComPtr () = default;
  ~ComPtr ();

 public:
  ComPtr (const ComPtr& other) noexcept;
  template <typename I_>
  ComPtr (const ComPtr<I_>& other) noexcept;
  ComPtr (ComPtr&& other) noexcept;

 public:
  ComPtr& operator= (const ComPtr& other) noexcept;
  template <typename I_>
  ComPtr& operator= (const ComPtr<I_>& other) noexcept;
  ComPtr& operator= (ComPtr&& other) noexcept;

 public:
  auto GetAdressOf () noexcept -> I**;
  auto Release () noexcept -> I*;
  void Reset (I* ptr = nullptr) noexcept;

 public:
  // Class dereference operator
  auto operator-> () const noexcept -> ComPtr_<I>*;
  auto operator& () noexcept -> I**;

 private:
  void IAddRef () noexcept;
  void IRelease () noexcept;

 private:
  I* ptr_ = nullptr;
};

////////////////////////////////////////////////////////////////////////////////
NAMESPACE_END (REngine::Core::Windows)
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Inline methods
////////////////////////////////////////////////////////////////////////////////
#include "ComPtr.inl"
////////////////////////////////////////////////////////////////////////////////
