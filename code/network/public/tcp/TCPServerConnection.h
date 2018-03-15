#ifndef GEMINI_NETWORK_TCPServerConnection_INCLUDE
#define GEMINI_NETWORK_TCPServerConnection_INCLUDE
#include "TCPConnection.h"

namespace gemini {

class GEMINI_NETWORK_API TCPServerConnection : public TCPConnection
{
public:
	TCPServerConnection();
	~TCPServerConnection();

	const String& getClientIP() const { return _clientIP; }
	void setClientIP(const String& ip) { _clientIP = ip; }

	UShort getClientPort() const { return _clientPort; }
	void setClientPort(UShort port) { _clientPort = port; }

protected:
	virtual std::shared_ptr<Socket> createSocket(boost::asio::io_service& ios) override;
	virtual Boolean execute(const MsgData& msg);
	virtual void close();
	virtual Boolean proHeartBeatTimeout();

private:
	String _clientIP;
	UShort _clientPort;
};

}

#endif // !GEMINI_NETWORK_ServiceTCP_INCLUDE
