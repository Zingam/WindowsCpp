#pragma once

////////////////////////////////////////////////////////////////////////////////
// Windows system headers
////////////////////////////////////////////////////////////////////////////////
#include <combaseapi.h>
////////////////////////////////////////////////////////////////////////////////
// The C Standard Library
#include <cstdint>
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Helper macro
////////////////////////////////////////////////////////////////////////////////

#if !defined (COM_INTERFACE)
#   define COM_INTERFACE(_com_interface_, _base_com_interface_, _uuid_) \
    interface __declspec(uuid(_uuid_)) _com_interface_ : _base_com_interface_
#endif // !defined (COM_INTERFACE)

////////////////////////////////////////////////////////////////////////////////
// IUnknown COM interfaces
////////////////////////////////////////////////////////////////////////////////

COM_INTERFACE (IPassangerCabin, IUnknown, 
    "{DC3C5FD6-EEC8-43AE-905A-6B9D86E812E8}")
{
    virtual auto Passangers () -> int = 0;
};

COM_INTERFACE (IMotor, IUnknown,
    "{D7ED6C2F-9DCB-4446-B841-A9EAF594440C}")
{
    virtual auto Power () -> int64_t = 0;
};

COM_INTERFACE (IVehicle, IUnknown, "{3539C134-F2F9-4DB5-AEA6-D5F80A0613A5}")
{
    virtual auto Speed () -> int64_t = 0;
};

////////////////////////////////////////////////////////////////////////////////
// Inheriting COM interfaces - Aircrafts
////////////////////////////////////////////////////////////////////////////////

COM_INTERFACE (IAircraft, IVehicle, "{C01EDF6A-2895-4928-B792-96FBF956D31D}")
{
    virtual auto Wings () -> int = 0;
};

// Aircraft types

COM_INTERFACE (IAirplane, IAircraft, "{888F8314-47C7-483D-A0CB-6EED95FE0CE9}")
{
    virtual void DisableAutopilot () = 0;
    virtual void EnableAutopilot () = 0;
};

COM_INTERFACE (IDrone, IAircraft, "{D890F0E7-49AA-4502-AAF1-EB18A85E6AC5}")
{
    virtual void TakePhoto () = 0;
};

COM_INTERFACE (IGlider, IAircraft, "{436D050A-979D-4EAC-A413-BA8B0BE3C637}")
{
    virtual void DropParachute () = 0;
};

////////////////////////////////////////////////////////////////////////////////
// Inheriting COM interfaces - Automobiles
////////////////////////////////////////////////////////////////////////////////

COM_INTERFACE (IAutomobile, IVehicle, "{61B13AB1-2E19-475D-8EFA-7BE2C9039EA0}")
{
    virtual void ShiftGear (int gear) = 0;
    virtual auto Wheels () -> int = 0;
};

////////////////////////////////////////////////////////////////////////////////
// Helper function
////////////////////////////////////////////////////////////////////////////////

template <typename T>
void ReleaseInterface (T*& ptr)
{
    if (nullptr != ptr)
    {
        ptr->Release ();
        ptr = nullptr;
    }
}

////////////////////////////////////////////////////////////////////////////////