#ifndef GEMINI_NETWORK_NetworkExport_INCLUDE
#define GEMINI_NETWORK_NetworkExport_INCLUDE
#include "../../core/public/Common.h"

#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
#ifdef GEMINI_NETWORK_EXPORTS
#define GEMINI_NETWORK_API __declspec(dllexport)
#else
#define GEMINI_NETWORK_API __declspec(dllimport)
#endif

#elif GEMINI_OS == GEMINI_OS_LINUX
#define GEMINI_NETWORK_API

#endif

#endif // GEMINI_NETWORK_NetworkExport_INCLUDE