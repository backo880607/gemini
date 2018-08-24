#ifndef GEMINI_USER_UserExport_INCLUDE
#define GEMINI_USER_UserExport_INCLUDE
#include "Common.h"

#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
#ifdef GEMINI_USER_EXPORTS
#define GEMINI_USER_API __declspec(dllexport)
#else
#define GEMINI_USER_API __declspec(dllimport)
#endif

#elif GEMINI_OS == GEMINI_OS_LINUX
#define GEMINI_USER_API

#endif

#endif  // GEMINI_USER_UserExport_INCLUDE