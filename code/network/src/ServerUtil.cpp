#include "../include/http/HTTPServer.h"
#include "../include/tcp/TCPServer.h"
#include "../public/ServerUtil.h"

namespace gemini {
namespace network {

TCPServer& getTCPServer() {
  static TCPServer server;
  return server;
}
Boolean ServerUtil::startTCPServer() { return getTCPServer().start(); }

void ServerUtil::stopTCPServer() { return getTCPServer().stop(); }

HTTPServer& getHTTPServer() {
  static HTTPServer server;
  return server;
}
Boolean ServerUtil::startHTTPServer() { return getHTTPServer().start(); }

void ServerUtil::stopHTTPServer() { return getHTTPServer().stop(); }

}  // namespace network
}  // namespace gemini