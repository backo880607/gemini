#ifndef GMINI_INTEGRATION_ImportExport_INCLUDE
#define GMINI_INTEGRATION_ImportExport_INCLUDE
#include "Core.h"

#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
#ifdef GEMINI_INTEGRATION_EXPORTS
#define GEMINI_INTEGRATION_API __declspec(dllexport)
#else
#define GEMINI_INTEGRATION_API __declspec(dllimport)
#endif

#elif GEMINI_OS == GEMINI_OS_LINUX
#define GEMINI_INTEGRATION_API

#endif

#endif  // GMINI_INTEGRATION_ImportExport_INCLUDE