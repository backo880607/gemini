#include "../../include/Socket.h"
#include "../../public/tcp/TCPConnection.h"

namespace gemini {
namespace network {

TCPConnection::TCPConnection() {}

TCPConnection::~TCPConnection() {}

void TCPConnection::bindIOS(boost::asio::io_service& ios) {
  _socket = createSocket(ios);
  _socket->weak_help = _socket;
}

}  // namespace network
}  // namespace gemini