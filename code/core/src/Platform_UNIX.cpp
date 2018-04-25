#include "Common.h"
#if GEMINI_OS == GEMINI_OS_LINUX
#include <unistd.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <sys/param.h>
#if defined(POCO_OS_FAMILY_BSD)
#include <sys/sysctl.h>
#elif POCO_OS == POCO_OS_HPUX
#include <pthread.h>
#endif

namespace gemini {

String Platform::getEnv(const Char* name)
{
    const char* val = getenv(name);
    return val != nullptr ? val : u8"";
}

Boolean Platform::hasEnv(const Char* name)
{
    return getenv(name) != nullptr;
}

void Platform::setEnv(const Char* name, const Char* value)
{
    std::string var = name;
	var.append("=");
	var.append(value);
	//_map[name] = var;
	//putenv((char*) _map[name].c_str())
}

String Platform::osName()
{
    struct utsname uts;
	uname(&uts);
	return uts.sysname;
}

String Platform::osDisplayName()
{
	return "";
    //return osNameImpl();
}

String Platform::osVersion()
{
    struct utsname uts;
	uname(&uts);
	return uts.release;
}

String Platform::osArchitecture()
{
    struct utsname uts;
	uname(&uts);
	return uts.machine;
}

String Platform::nodeName()
{
    struct utsname uts;
	uname(&uts);
	return uts.nodename;
}

String Platform::osID()
{
	return "";
}

String Platform::CPUID()
{
	return "";
}

String Platform::mainDiskID()
{
	return "";
}

String Platform::mainBoardID()
{
	return "";
}

String Platform::macAddress()
{
	return "";
}

}
#endif