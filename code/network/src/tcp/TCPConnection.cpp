#include "../../public/tcp/TCPConnection.h"
#include "../../include/Socket.h"

namespace gemini {

TCPConnection::TCPConnection()
{

}

TCPConnection::~TCPConnection()
{
}

void TCPConnection::bindIOS(boost::asio::io_service & ios) {
	_socket = createSocket(ios);
	_socket->weak_help = _socket;
}

}