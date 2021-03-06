#include "UDLiterals.hpp"
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// User defined literals
////////////////////////////////////////////////////////////////////////////////

unsigned long long
operator ""_hp (unsigned long long power)
{
    return power;
}

unsigned long long
operator ""_kmh (unsigned long long speed)
{
    return speed;
}

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////////////////////////

bool check_bitness ()
{
    const auto pointerSize = sizeof (void*);
    // Do not allow compilation on non 64bit architectures
    static_assert((8 <= pointerSize), "===> ERROR: 64bit architectures are supported only");

    return pointerSize;
}

////////////////////////////////////////////////////////////////////////////////
