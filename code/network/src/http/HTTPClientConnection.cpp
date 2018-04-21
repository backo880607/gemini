#include "../../public/http/HTTPClientConnection.h"
#include "../../include/HTTPSocket.h"

namespace gemini {

HTTPClientConnection::HTTPClientConnection()
{
}

HTTPClientConnection::~HTTPClientConnection()
{

}

std::shared_ptr<Socket> HTTPClientConnection::createSocket(boost::asio::io_service& ios) {
	return std::shared_ptr<Socket>(new HTTPSocket(ios, this, 100));
}
}