#include "../../include/Socket.h"
#include "../../public/tcp/TCPServerConnection.h"

namespace gemini {
namespace network {

TCPServerConnection::TCPServerConnection() {}

TCPServerConnection::~TCPServerConnection() {}

std::shared_ptr<Socket> TCPServerConnection::createSocket(
    boost::asio::io_service& ios) {
  return std::shared_ptr<Socket>(new Socket(ios, this, 100));
}

Boolean TCPServerConnection::execute(const api::MsgData& msg) {
  return Boolean();
}

void TCPServerConnection::close() {}

Boolean TCPServerConnection::proHeartBeatTimeout() { return Boolean(); }

}  // namespace network
}  // namespace gemini