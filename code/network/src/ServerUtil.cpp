#include "../public/ServerUtil.h"
#include "../include/tcp/TCPServer.h"
#include "../include/http/HTTPServer.h"

namespace gemini {

Boolean ServerUtil::startTCPServer() {
	TCPServer server;
	return server.start();
}

Boolean ServerUtil::startHTTPServer() {
	HTTPServer server;
	return server.start();
}

}