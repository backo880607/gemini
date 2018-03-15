#include "../../include/http/HTTPServer.h"
#include "../../public/http/HTTPServerConnection.h"

namespace gemini {

HTTPServer::HTTPServer()
{

}

HTTPServer::~HTTPServer()
{

}

std::shared_ptr<TCPServerConnection> HTTPServer::createConnection()
{
	return std::shared_ptr<TCPServerConnection>(new HTTPServerConnection());
}

}