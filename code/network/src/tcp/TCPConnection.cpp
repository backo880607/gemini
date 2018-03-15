#include "../../public/tcp/TCPConnection.h"
#include "../../include/Socket.h"
#include "../../include/http/HTTPServerSocket.h"
#include "../../public/http/HTTPServerConnection.h"

namespace gemini {

TCPConnection::TCPConnection()
{

}

TCPConnection::~TCPConnection()
{
}

void TCPConnection::bindIOS(boost::asio::io_service & ios)
{
	if (typeid(*this) == typeid(HTTPServerConnection)) {
		_socket.reset(new HTTPServerSocket(ios, this, 100));
	} else {
		_socket.reset(new Socket(ios, this, 100));
	}
	_socket->weak_help = _socket;
}

}