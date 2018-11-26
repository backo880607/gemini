#include "../../include/HTTPSocket.h"
#include "../../public/http/HTTPServerConnection.h"

namespace gemini {
namespace network {

std::shared_ptr<Socket> HTTPServerConnection::createSocket(
    boost::asio::io_service& ios) {
  return std::shared_ptr<Socket>(new HTTPSocket(ios, this, 100));
}

}  // namespace network
}  // namespace gemini