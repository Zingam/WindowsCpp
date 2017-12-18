#pragma once

////////////////////////////////////////////////////////////////////////////////
#include <cstdint>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// User defined literals
////////////////////////////////////////////////////////////////////////////////

auto operator ""_hp (unsigned long long power) -> unsigned long long;

auto operator ""_kmh (unsigned long long speed) -> unsigned long long;

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

auto check_bitness () -> bool;

////////////////////////////////////////////////////////////////////////////////