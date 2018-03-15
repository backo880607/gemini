#ifndef GEMINI_NETWORK_ServerUtil_INCLUDE
#define GEMINI_NETWORK_ServerUtil_INCLUDE
#include "NetworkExport.h"

namespace gemini {

class GEMINI_NETWORK_API ServerUtil
{
public:
	static Boolean startTCPServer();
	static Boolean startHTTPServer();
};

}
#endif // GEMINI_NETWORK_ServerUtil_INCLUDE
