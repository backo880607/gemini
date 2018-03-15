#ifndef GEMINI_DATA_DataExport_INCLUDE
#define GEMINI_DATA_DataExport_INCLUDE
#include "../../core/public/Common.h"

#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
#ifdef GEMINI_DATA_EXPORTS
#define GEMINI_DATA_API __declspec(dllexport)
#else
#define GEMINI_DATA_API __declspec(dllimport)
#endif

#elif GEMINI_OS == GEMINI_OS_LINUX
#define GEMINI_DATA_API

#endif

#endif // GEMINI_DATA_DataExport_INCLUDE