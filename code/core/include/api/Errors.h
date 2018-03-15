#ifndef GEMINI_API_Errors_INCLUDE
#define GEMINI_API_Errors_INCLUDE
#include "../../public/message/Message.h"

namespace gemini {

class ProcessLaunchError : public log_info
{
public:
	virtual String getName() override { return u8"ProcessLaunch"; }
};

class ProcessKillError : public log_info
{
public:
	virtual String getName() override { return u8"ProcessKill"; }
};

class ProcessWaitError : public log_info
{
public:
	virtual String getName() override { return u8"ProcessWait"; }
};

}
#endif // GEMINI_API_Errors_INCLUDE
