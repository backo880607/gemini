#ifndef GEMINI_DumpFile_INCLUDE
#define GEMINI_DumpFile_INCLUDE
#include "../public/Common.h"

namespace google_breakpad { class ExceptionHandler; }
namespace gemini {

class CORE_API DumpFile
{
	DumpFile(void);
	DumpFile(const DumpFile&) {}
	~DumpFile(void);
	DumpFile& operator= (const DumpFile&) { return *this; }
public:
	static DumpFile& instance() { static DumpFile obj; return obj; }

	void Init();

private:
	google_breakpad::ExceptionHandler* m_pCrashHandler;
};

}

#endif // GEMINI_DumpFile_INCLUDE
