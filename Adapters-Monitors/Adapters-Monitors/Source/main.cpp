// System headers
#include <Windows.h>
// Always include after Windows.h
#include <Shellapi.h>
// C++ Standard headers
#include <string>
#include <vector>

int
  main ()
{
  //////////////////////////////////////////////////////////////////////////////
  // Parse the command line arguments
  //////////////////////////////////////////////////////////////////////////////
  
  // Retrieve the command line arguments in UNICODE
  auto lpCmdLine = GetCommandLineW ();
  int numArgs = 0;
  auto argList = CommandLineToArgvW (lpCmdLine, &numArgs);
  // Free memory allocated for CommandLineToArgvW arguments.
  LocalFree (argList);

  //////////////////////////////////////////////////////////////////////////////
  // Enumerated the display devices
  //////////////////////////////////////////////////////////////////////////////
  

  DISPLAY_DEVICE displayDevice;
  displayDevice.cb = sizeof (DISPLAY_DEVICE);
  EnumDisplayDevices (nullptr, 0, &displayDevice, 0);

  auto displayConfigFlags = QDC_ONLY_ACTIVE_PATHS;
  UINT32 pNumPathArrayElements = 0;
  std::vector<DISPLAYCONFIG_PATH_INFO> pPathInfoArray{};
  UINT32 pNumModeInfoArrayElements = 0;
  std::vector<DISPLAYCONFIG_MODE_INFO> pModeInfoArray{};
  GetDisplayConfigBufferSizes (
    displayConfigFlags, &pNumPathArrayElements, &pNumModeInfoArrayElements);
  pPathInfoArray.resize (pNumPathArrayElements);
  pModeInfoArray.resize (pNumModeInfoArrayElements);
  auto result = QueryDisplayConfig (displayConfigFlags,
                                    &pNumPathArrayElements,
                                    pPathInfoArray.data (),
                                    &pNumModeInfoArrayElements,
                                    pModeInfoArray.data (),
                                    nullptr);
  std::string error{};
  switch (result)
  {
    case ERROR_SUCCESS:
      error = "The function succeeded.";
      break;

    case ERROR_INVALID_PARAMETER:
      error = "The combination of parameters and flags that are specified is "
              "invalid.";
      break;

    case ERROR_NOT_SUPPORTED:
      error =
        "The system is not running a graphics driver that was written "
        "according to the Windows Display Driver Model (WDDM). The function is "
        "only supported on a system with a WDDM driver running.";
      break;

    case ERROR_ACCESS_DENIED:
      error = "The caller does not have access to the console session.This "
              "error occurs if the calling process does not have access to the "
              "current desktop or is running on a remote session.";
      break;

    case ERROR_GEN_FAILURE:
      error = "An unspecified error occurred.";
      break;

    case ERROR_INSUFFICIENT_BUFFER:
      error = "The supplied path and mode buffer are too small.";
      break;
  }

  for (auto& pPathInfo : pPathInfoArray)
  {
    DISPLAYCONFIG_TARGET_DEVICE_NAME requestPacket{};
    requestPacket.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
    requestPacket.header.size = sizeof (DISPLAYCONFIG_TARGET_DEVICE_NAME);
    requestPacket.header.adapterId = pPathInfo.targetInfo.adapterId;
    requestPacket.header.id = pPathInfo.targetInfo.id;
    result = DisplayConfigGetDeviceInfo (&requestPacket.header);
    std::wstring monitorName = requestPacket.monitorFriendlyDeviceName;
    std::wstring monitorDevicePath = requestPacket.monitorDevicePath;

    switch (result)
    {
      case ERROR_SUCCESS:
        error = "The function succeeded.";
        break;

      case ERROR_INVALID_PARAMETER:
        error =
          "The combination of parameters and flags specified are invalid.";
        break;

      case ERROR_NOT_SUPPORTED:
        error =
          "The system is not running a graphics driver that was written "
          "according to the Windows Display Driver Model (WDDM). The function "
          "is only supported on a system with a WDDM driver running.";
        break;

      case ERROR_ACCESS_DENIED:
        error =
          "The caller does not have access to the console session. This error "
          "occurs if the calling process does not have access to the current "
          "desktop or is running on a remote session.";
        break;

      case ERROR_INSUFFICIENT_BUFFER:
        error =
          "The size of the packet that the caller passes is not big enough for "
          "the information that the caller requests.";
        break;

      case ERROR_GEN_FAILURE:
        error = "An unspecified error occurred.";
        break;
    }
  }

  for (auto& pPathInfo : pPathInfoArray)
  {
    DISPLAYCONFIG_SOURCE_DEVICE_NAME requestPacket{};
    requestPacket.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
    requestPacket.header.size = sizeof (DISPLAYCONFIG_SOURCE_DEVICE_NAME);
    requestPacket.header.adapterId = pPathInfo.sourceInfo.adapterId;
    requestPacket.header.id = pPathInfo.sourceInfo.id;
    result = DisplayConfigGetDeviceInfo (&requestPacket.header);
    std::wstring monitorName = requestPacket.viewGdiDeviceName;

    switch (result)
    {
      case ERROR_SUCCESS:
        error = "The function succeeded.";
        break;

      case ERROR_INVALID_PARAMETER:
        error =
          "The combination of parameters and flags specified are invalid.";
        break;

      case ERROR_NOT_SUPPORTED:
        error =
          "The system is not running a graphics driver that was written "
          "according to the Windows Display Driver Model (WDDM). The function "
          "is only supported on a system with a WDDM driver running.";
        break;

      case ERROR_ACCESS_DENIED:
        error =
          "The caller does not have access to the console session. This error "
          "occurs if the calling process does not have access to the current "
          "desktop or is running on a remote session.";
        break;

      case ERROR_INSUFFICIENT_BUFFER:
        error =
          "The size of the packet that the caller passes is not big enough for "
          "the information that the caller requests.";
        break;

      case ERROR_GEN_FAILURE:
        error = "An unspecified error occurred.";
        break;
    }
  }

  for (auto& pPathInfo : pPathInfoArray)
  {
    DISPLAYCONFIG_ADAPTER_NAME requestPacket{};
    requestPacket.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_ADAPTER_NAME;
    requestPacket.header.size = sizeof (DISPLAYCONFIG_ADAPTER_NAME);
    requestPacket.header.adapterId = pPathInfo.sourceInfo.adapterId;
    requestPacket.header.id = pPathInfo.sourceInfo.id;
    result = DisplayConfigGetDeviceInfo (&requestPacket.header);
    std::wstring monitorName = requestPacket.adapterDevicePath;

    switch (result)
    {
      case ERROR_SUCCESS:
        error = "The function succeeded.";
        break;

      case ERROR_INVALID_PARAMETER:
        error =
          "The combination of parameters and flags specified are invalid.";
        break;

      case ERROR_NOT_SUPPORTED:
        error =
          "The system is not running a graphics driver that was written "
          "according to the Windows Display Driver Model (WDDM). The function "
          "is only supported on a system with a WDDM driver running.";
        break;

      case ERROR_ACCESS_DENIED:
        error =
          "The caller does not have access to the console session. This error "
          "occurs if the calling process does not have access to the current "
          "desktop or is running on a remote session.";
        break;

      case ERROR_INSUFFICIENT_BUFFER:
        error =
          "The size of the packet that the caller passes is not big enough for "
          "the information that the caller requests.";
        break;

      case ERROR_GEN_FAILURE:
        error = "An unspecified error occurred.";
        break;
    }
  }

  for (auto& pPathInfo : pPathInfoArray)
  {
    DISPLAYCONFIG_ADAPTER_NAME requestPacket{};
    requestPacket.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_ADAPTER_NAME;
    requestPacket.header.size = sizeof (DISPLAYCONFIG_ADAPTER_NAME);
    requestPacket.header.adapterId = pPathInfo.targetInfo.adapterId;
    requestPacket.header.id = pPathInfo.targetInfo.id;
    result = DisplayConfigGetDeviceInfo (&requestPacket.header);
    std::wstring monitorName = requestPacket.adapterDevicePath;

    switch (result)
    {
      case ERROR_SUCCESS:
        error = "The function succeeded.";
        break;

      case ERROR_INVALID_PARAMETER:
        error =
          "The combination of parameters and flags specified are invalid.";
        break;

      case ERROR_NOT_SUPPORTED:
        error =
          "The system is not running a graphics driver that was written "
          "according to the Windows Display Driver Model (WDDM). The function "
          "is only supported on a system with a WDDM driver running.";
        break;

      case ERROR_ACCESS_DENIED:
        error =
          "The caller does not have access to the console session. This error "
          "occurs if the calling process does not have access to the current "
          "desktop or is running on a remote session.";
        break;

      case ERROR_INSUFFICIENT_BUFFER:
        error =
          "The size of the packet that the caller passes is not big enough for "
          "the information that the caller requests.";
        break;

      case ERROR_GEN_FAILURE:
        error = "An unspecified error occurred.";
        break;
    }
  }

  auto r = MonitorFromWindow (nullptr, MONITOR_DEFAULTTOPRIMARY);
}