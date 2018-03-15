#ifndef GEMINI_NETWORK_HTTPServer_INCLUDE
#define GEMINI_NETWORK_HTTPServer_INCLUDE
#include "../tcp/TCPServer.h"

namespace gemini {

class HTTPServer : public TCPServer
{
public:
	HTTPServer();
	virtual ~HTTPServer();

protected:
	virtual std::shared_ptr<TCPServerConnection> createConnection();
};

}
#endif // GEMINI_NETWORK_HTTPServer_INCLUDE
