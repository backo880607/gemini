#ifndef GEMINI_NETWORK_NetworkError_INCLUDE
#define GEMINI_NETWORK_NetworkError_INCLUDE
#include "NetworkExport.h"
#include "../public/message/Exception.h"

namespace gemini {

class GEMINI_NETWORK_API NetworkException : public gemini::Exception
{
public:
	virtual String getName() const override { return u8"NetworkException"; }
};

}
#endif // GEMINI_NETWORK_NetworkError_INCLUDE
