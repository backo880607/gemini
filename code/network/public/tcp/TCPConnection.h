#ifndef GEMINI_NETWORK_TCPConnection_INCLUDE
#define GEMINI_NETWORK_TCPConnection_INCLUDE
#include "../../../core/public/Object.h"
#include "../../../core/public/api/MsgData.h"
#include "../NetworkExport.h"

namespace boost {
namespace asio {
class io_context;
typedef io_context io_service;
}  // namespace asio
}  // namespace boost

namespace gemini {

class Socket;
class GEMINI_NETWORK_API TCPConnection {
  typedef std::shared_ptr<Socket> socket_type;

 public:
  TCPConnection();
  virtual ~TCPConnection();

  socket_type get() { return _socket; }

  void bindIOS(boost::asio::io_service& ios);

 protected:
  virtual std::shared_ptr<Socket> createSocket(
      boost::asio::io_service& ios) = 0;
  virtual Boolean execute(const MsgData& msg) = 0;

  virtual void close() = 0;

  /**
   * @brief 心跳超时处理
   * @return 返回是否关闭TCP连接
   */
  virtual Boolean proHeartBeatTimeout() = 0;

 private:
  friend class Socket;
  socket_type _socket;
};

}  // namespace gemini
#endif  // GEMINI_NETWORK_TCPConnection_INCLUDE
