////////////////////////////////////////////////////////////////////////////////
#include <Vehicles/Vehicles>
////////////////////////////////////////////////////////////////////////////////
// The C++ Standard Library
////////////////////////////////////////////////////////////////////////////////
#include <sstream>
////////////////////////////////////////////////////////////////////////////////

int main (int argc, const char* argv [])
{
    ////////////////////////////////////////////////////////////////////////////
    // COM interfaces
    ////////////////////////////////////////////////////////////////////////////

    auto [vehicle, result] = CreateAutomobile ();

    IAutomobile* automobile = nullptr;
    result = vehicle->QueryInterface<IAutomobile> (&automobile);
    if (S_OK == result)
    {
        automobile->ShiftGear (5);
        automobile->Release ();
        automobile = nullptr;
    }

    IAirplane* airplane = nullptr;
    result = vehicle->QueryInterface<IAirplane> (&airplane);
    switch (result)
    {
        case S_OK:
        {
            airplane->EnableAutopilot ();
            airplane->Release ();

            break;
        }
        case E_NOINTERFACE:
        {
            OutputDebugString ("COM error: Interface IAircraft not supported\n");

            break;
        }
        default:
        {
            _ASSERT_EXPR (false, "Unknown error");
        }
    }

    ReleaseInterface<IVehicle> (vehicle);
    
    ////////////////////////////////////////////////////////////////////////////
    // ComPtr
    ////////////////////////////////////////////////////////////////////////////

    REngine::Core::Windows::ComPtr<IVehicle> smartVehicle;

    result = CreateAirplane (&smartVehicle);
    switch (result)
    {
        case S_OK:
        {
            auto s = smartVehicle->Speed ();

            std::stringstream ss;

            OLECHAR* guidString;
            StringFromCLSID (__uuidof (smartVehicle), &guidString);
            ss << "COM Object is 'IVehicle' - GUID = " << guidString << "\n";
            ::CoTaskMemFree (guidString);

            ss << "    Speed:      " << s << "km/h\n";

            OutputDebugString (ss.str ().c_str ());

            break;
        }
        case E_OUTOFMEMORY:
        {
            break;
        }
        default:
        {
            _ASSERT_EXPR (false, "Unknown error");
        }
    }

    REngine::Core::Windows::ComPtr<IMotor> motor;
    result = smartVehicle->QueryInterface<IMotor> (&motor);
    switch (result)
    {
        case S_OK:
        {
            auto p = motor->Power ();

            std::stringstream ss;

            OLECHAR* guidString;
            StringFromCLSID (__uuidof (motor), &guidString);
            ss << "COM Object is 'IMotor' - GUID = " << guidString << "\n";
            ::CoTaskMemFree (guidString);

            ss << "    Power:      " << p << "km/h\n";

            OutputDebugString (ss.str ().c_str ());

            break;
        }
        case E_OUTOFMEMORY:
        {
            break;
        }
        default:
        {
            _ASSERT_EXPR (false, "Unknown error");
        }
    }
}
