#ifndef GEMINI_NETWORK_HTTPServerConnection_INCLUDE
#define GEMINI_NETWORK_HTTPServerConnection_INCLUDE
#include "../tcp/TCPServerConnection.h"

namespace gemini {

class GEMINI_NETWORK_API HTTPServerConnection : public TCPServerConnection
{
public:
protected:
	virtual std::shared_ptr<Socket> createSocket(boost::asio::io_service& ios) override;
};

}
#endif // GEMINI_NETWORK_HTTPServerConnection_INCLUDE
