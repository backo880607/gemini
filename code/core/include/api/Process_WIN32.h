#ifndef GEMINI_Process_WIN32_INCLUDE
#define GEMINI_Process_WIN32_INCLUDE
#include "../../public/Common.h"

#if GEMINI_OS == GEMINI_OS_WINDOWS_NT
#include <Windows.h>
#undef ERROR

namespace gemini {

class ProcessImpl
{
	typedef std::vector<String> Args;
public:
	ProcessImpl(HANDLE _hProcess, Long pid);
	~ProcessImpl();

	Long id() const;
	HANDLE process() const;
	Boolean running() const;
	Int wait() const;
	void kill();

	static Long currentId();
	static std::shared_ptr<ProcessImpl> launch(const String& command, const Args& args);
private:
	HANDLE _hProcess;
	Long _pid;
};

}
#endif

#endif // GEMINI_Process_WIN32_INCLUDE
