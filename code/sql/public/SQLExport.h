#ifndef GEMINI_SQL_SQLExport_INCLUDE
#define GEMINI_SQL_SQLExport_INCLUDE
#include "../../core/public/Common.h"

#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
#ifdef GEMINI_SQL_EXPORTS
#define GEMINI_SQL_API __declspec(dllexport)
#else
#define GEMINI_SQL_API __declspec(dllimport)
#endif

#elif GEMINI_OS == GEMINI_OS_LINUX
#define GEMINI_SQL_API

#endif

#endif // GEMINI_SQL_SQLExport_INCLUDE