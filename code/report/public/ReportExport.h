#ifndef GEMINI_REPORT_ReportExport_INCLUDE
#define GEMINI_REPORT_ReportExport_INCLUDE
#include "Common.h"

#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
#ifdef GEMINI_REPORT_EXPORTS
#define GEMINI_REPORT_API __declspec(dllexport)
#else
#define GEMINI_REPORT_API __declspec(dllimport)
#endif

#elif GEMINI_OS == GEMINI_OS_LINUX
#define GEMINI_REPORT_API

#endif

#endif  // GEMINI_REPORT_ReportExport_INCLUDE