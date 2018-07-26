#include "Common.h"
#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
#include <winsock2.h>
#include <windows.h>
#include <iphlpapi.h>
#include <wincrypt.h>
#include <sstream>

#define _WIN32_DCOM
#include <comdef.h>
#include <wbemidl.h>
#pragma comment(lib, "wbemuuid.lib")

namespace gemini {

String Platform::getEnv(const Char* name) {
  DWORD len = GetEnvironmentVariableA(name, 0, 0);
  if (len == 0) return "";
  char* buffer = new char[len];
  GetEnvironmentVariableA(name, buffer, len);
  std::string result(buffer);
  delete[] buffer;
  return result;
}

Boolean Platform::hasEnv(const Char* name) {
  return GetEnvironmentVariableA(name, 0, 0) > 0;
}

void Platform::setEnv(const Char* name, const Char* value) {
  SetEnvironmentVariableA(name, value);
}

String Platform::osName() {
  OSVERSIONINFO vi;
  vi.dwOSVersionInfoSize = sizeof(vi);
  if (GetVersionEx(&vi) == 0) return u8"";
  switch (vi.dwPlatformId) {
    case VER_PLATFORM_WIN32s:
      return "Windows 3.x";
    case VER_PLATFORM_WIN32_WINDOWS:
      return vi.dwMinorVersion == 0 ? "Windows 95" : "Windows 98";
    case VER_PLATFORM_WIN32_NT:
      return "Windows NT";
    default:
      return "Unknown";
  }
}

String Platform::osDisplayName() {
  OSVERSIONINFOEX vi;  // OSVERSIONINFOEX is supported starting at Windows 2000
  vi.dwOSVersionInfoSize = sizeof(vi);
  if (GetVersionEx((OSVERSIONINFO*)&vi) == 0) return "";
  switch (vi.dwMajorVersion) {
    case 10:
      switch (vi.dwMinorVersion) {
        case 0:
          return vi.wProductType == VER_NT_WORKSTATION ? "Windows 10"
                                                       : "Windows Server 2016";
      }
    case 6:
      switch (vi.dwMinorVersion) {
        case 0:
          return vi.wProductType == VER_NT_WORKSTATION ? "Windows Vista"
                                                       : "Windows Server 2008";
        case 1:
          return vi.wProductType == VER_NT_WORKSTATION
                     ? "Windows 7"
                     : "Windows Server 2008 R2";
        case 2:
          return vi.wProductType == VER_NT_WORKSTATION ? "Windows 8"
                                                       : "Windows Server 2012";
        case 3:
          return vi.wProductType == VER_NT_WORKSTATION
                     ? "Windows 8.1"
                     : "Windows Server 2012 R2";
        default:
          return "Unknown";
      }
    case 5:
      switch (vi.dwMinorVersion) {
        case 0:
          return "Windows 2000";
        case 1:
          return "Windows XP";
        case 2:
          return "Windows Server 2003/Windows Server 2003 R2";
        default:
          return "Unknown";
      }
    default:
      return "Unknown";
  }
}

String Platform::osVersion() {
  OSVERSIONINFO vi;
  vi.dwOSVersionInfoSize = sizeof(vi);
  if (GetVersionEx(&vi) == 0) return "";
  std::ostringstream str;
  str << vi.dwMajorVersion << "." << vi.dwMinorVersion << " (Build "
      << (vi.dwBuildNumber & 0xFFFF);
  if (vi.szCSDVersion[0]) str << ": " << vi.szCSDVersion;
  str << ")";
  return str.str();
}

String Platform::osArchitecture() {
  SYSTEM_INFO si;
  GetSystemInfo(&si);
  switch (si.wProcessorArchitecture) {
    case PROCESSOR_ARCHITECTURE_INTEL:
      return "IA32";
    case PROCESSOR_ARCHITECTURE_MIPS:
      return "MIPS";
    case PROCESSOR_ARCHITECTURE_ALPHA:
      return "ALPHA";
    case PROCESSOR_ARCHITECTURE_PPC:
      return "PPC";
    case PROCESSOR_ARCHITECTURE_IA64:
      return "IA64";
#ifdef PROCESSOR_ARCHITECTURE_IA32_ON_WIN64
    case PROCESSOR_ARCHITECTURE_IA32_ON_WIN64:
      return "IA64/32";
#endif
#ifdef PROCESSOR_ARCHITECTURE_AMD64
    case PROCESSOR_ARCHITECTURE_AMD64:
      return "AMD64";
#endif
    default:
      return "Unknown";
  }
}

String Platform::nodeName() {
  char name[MAX_COMPUTERNAME_LENGTH + 1];
  DWORD size = sizeof(name);
  if (GetComputerNameA(name, &size) == 0) return "";
  return std::string(name);
}

String Platform::osID() { return ""; }

String Platform::CPUID() { return ""; }

String Platform::mainDiskID() { return ""; }

String Platform::mainBoardID() { return ""; }

String Platform::macAddress() { return ""; }

}  // namespace gemini
#endif