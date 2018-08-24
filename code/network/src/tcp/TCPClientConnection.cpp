#include "../../include/Socket.h"
#include "../../public/tcp/TCPClientConnection.h"

#include <boost/asio.hpp>

namespace gemini {

boost::asio::io_service g_clientIOService;
TCPClientConnection::TCPClientConnection() { bindIOS(g_clientIOService); }

TCPClientConnection::~TCPClientConnection() {}

Boolean TCPClientConnection::login(const String& user, const String& password) {
  return Boolean();
}

Boolean TCPClientConnection::login(const String& user, const String& password,
                                   String& errMsg) {
  return Boolean();
}

Boolean TCPClientConnection::logout() { return Boolean(); }

std::shared_ptr<Socket> TCPClientConnection::createSocket(
    boost::asio::io_service& ios) {
  return std::shared_ptr<Socket>(new Socket(ios, this, 100));
}

Boolean TCPClientConnection::execute(const MsgData& msg) { return Boolean(); }

void TCPClientConnection::close() {}

Boolean TCPClientConnection::proHeartBeatTimeout() { return Boolean(); }

}  // namespace gemini