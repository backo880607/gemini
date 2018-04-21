#include "../../public/tcp/TCPServerConnection.h"
#include "../../include/Socket.h"

namespace gemini {

TCPServerConnection::TCPServerConnection()
{
}

TCPServerConnection::~TCPServerConnection()
{
}

std::shared_ptr<Socket> TCPServerConnection::createSocket(boost::asio::io_service & ios) {
	return std::shared_ptr<Socket>(new Socket(ios, this, 100));
}

Boolean TCPServerConnection::execute(const MsgData & msg) {
	return Boolean();
}

void TCPServerConnection::close() {
}

Boolean TCPServerConnection::proHeartBeatTimeout() {
	return Boolean();
}

}