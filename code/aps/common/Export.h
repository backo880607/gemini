#pragma once
#include "Object.h"

#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
#pragma warning(disable:4251)
#pragma warning(disable:4275)
#pragma warning(disable:4099)
#ifdef APS_EXPORTS
#define APS_API __declspec(dllexport)
#else
#define APS_API __declspec(dllimport)
#endif

#elif GEMINI_OS == GEMINI_OS_LINUX
#define APS_API

#endif

APS_API void initAPS();