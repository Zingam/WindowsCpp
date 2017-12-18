////////////////////////////////////////////////////////////////////////////////
#include "Automobile.hpp"
////////////////////////////////////////////////////////////////////////////////
// Windows system headers
////////////////////////////////////////////////////////////////////////////////
#include <crtdbg.h>
////////////////////////////////////////////////////////////////////////////////
// The C++ Standard Library
////////////////////////////////////////////////////////////////////////////////
#include <sstream>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// class Automobile
////////////////////////////////////////////////////////////////////////////////

// Constructors and destructors

Automobile::Automobile ()
{
    OutputDebugString ("Object of class 'Automobile' created\n");
}

Automobile::~Automobile ()
{
    OutputDebugString ("Object of class 'Automobile' destroyed\n");
}

// Inherited methods - IAutomobile

void
Automobile::ShiftGear (int gear)
{
    this->gear = gear;

    std::stringstream ss;
    ss << "Automobile: Gear shifted -> " << gear << "\n";

    OutputDebugString (ss.str ().c_str ());
}

int
Automobile::Wheels ()
{
    return this->wheels;
}

// Inherited methods - IMotor

int64_t
Automobile::Power ()
{
    return this->power;
}

// Inherited methods - IPassangerCabin

int
Automobile::Passangers ()
{
    return this->passangers;
}

// Inherited methods - IVehicle

int64_t
Automobile::Speed ()
{
    return this->speed;
}

// Inherited methods - IUnknown

unsigned long 
Automobile::AddRef ()
{
    return _InterlockedIncrement (&this->count);
}

unsigned long 
Automobile::Release ()
{
    auto result = _InterlockedDecrement (&this->count);

    if (0 == result)
    {
        delete this;
    }

    return result;
}

HRESULT 
Automobile::QueryInterface (IID const& id, void** result)
{
    _ASSERTE (result);

    if ((id == __uuidof (IAutomobile))
        || (id == __uuidof (IVehicle))
        || (id == __uuidof (IUnknown)))
    {
        *result = static_cast<IAutomobile*> (this);
    }
    else if (id == __uuidof (IMotor))
    {
        *result = static_cast<IMotor*> (this);
    }
    else if (id == __uuidof (IPassangerCabin))
    {
        *result = static_cast<IPassangerCabin*> (this);
    }
    else
    {
        *result = 0;

        return E_NOINTERFACE;
    }

    static_cast<IUnknown*> (*result)->AddRef ();

    return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
