#ifndef GEMINI_NETWORK_HTTPClientConnection_INCLUDE
#define GEMINI_NETWORK_HTTPClientConnection_INCLUDE
#include "../tcp/TCPClientConnection.h"

namespace gemini {

class GEMINI_NETWORK_API HTTPClientConnection : public TCPClientConnection {
 public:
  HTTPClientConnection();
  virtual ~HTTPClientConnection();

 protected:
  virtual std::shared_ptr<Socket> createSocket(
      boost::asio::io_service& ios) override;
};

}  // namespace gemini
#endif  // GEMINI_NETWORK_HTTPClientConnection_INCLUDE
