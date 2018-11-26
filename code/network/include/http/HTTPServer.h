#ifndef GEMINI_NETWORK_HTTPServer_INCLUDE
#define GEMINI_NETWORK_HTTPServer_INCLUDE
#include "../tcp/TCPServer.h"

namespace gemini {
namespace network {

class HTTPServer : public TCPServer {
 public:
  HTTPServer();
  virtual ~HTTPServer();

 protected:
  virtual std::shared_ptr<TCPServerConnection> createConnection();
};

}  // namespace network
}  // namespace gemini
#endif  // GEMINI_NETWORK_HTTPServer_INCLUDE