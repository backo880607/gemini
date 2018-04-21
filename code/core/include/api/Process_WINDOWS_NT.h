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
#endif // GEMINI_Process_WINDOWS_NT_INCLUDE
