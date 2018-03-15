#include "../include/HTTPSocket.h"

namespace gemini {

HTTPSocket::HTTPSocket(service_type& ios, TCPConnection* conn, UInt hbTimeout)
	: Socket(ios, conn, hbTimeout)
{

}

HTTPSocket::~HTTPSocket()
{

}

}
