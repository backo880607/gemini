#ifndef GEMINI_LICENSE_LicenseExport_INCLUDE
#define GEMINI_LICENSE_LicenseExport_INCLUDE
#include "Common.h"

#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
#ifdef GEMINI_LICENSE_EXPORTS
#define GEMINI_LICENSE_API __declspec(dllexport)
#else
#define GEMINI_LICENSE_API __declspec(dllimport)
#endif

#elif GEMINI_OS == GEMINI_OS_LINUX
#define GEMINI_LICENSE_API

#endif

#endif  // GEMINI_LICENSE_LicenseExport_INCLUDE