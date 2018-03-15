#ifndef GEMINI_NETWORK_HTTPSocket_INCLUDE
#define GEMINI_NETWORK_HttpSocket_INCLUDE
#include "Socket.h"

namespace gemini {

class HTTPSocket : public Socket
{
public:
	HTTPSocket(service_type& ios, TCPConnection* conn, UInt hbTimeout);
	~HTTPSocket();
};

}
#endif // GEMINI_NETWORK_HttpSocket_INCLUDE
