#include "../../include/HTTPSocket.h"
#include "../../public/http/HTTPClientConnection.h"

namespace gemini {
namespace network {

HTTPClientConnection::HTTPClientConnection() {}

HTTPClientConnection::~HTTPClientConnection() {}

std::shared_ptr<Socket> HTTPClientConnection::createSocket(
    boost::asio::io_service& ios) {
  return std::shared_ptr<Socket>(new HTTPSocket(ios, this, 100));
}

}  // namespace network
}  // namespace gemini