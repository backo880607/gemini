#ifndef GEMINI_Process_WINDOWS_NT_INCLUDE
#define GEMINI_Process_WINDOWS_NT_INCLUDE
#include "../../public/Common.h"

#include <Windows.h>
#undef ERROR

namespace gemini {

class ProcessImpl
{
	typedef std::vector<String> Args;
public:
	ProcessImpl(HANDLE _hProcess, ULong pid);
	~ProcessImpl();

	ULong id() const;
	HANDLE process() const;
	Boolean running() const;
	Int wait() const;
	void kill();

	static ULong currentId();
	static std::shared_ptr<ProcessImpl> launch(const String& command, const Args& args);
private:
	HANDLE _hProcess;
	ULong _pid;
};

}
#endif // GEMINI_Process_WINDOWS_NT_INCLUDE
