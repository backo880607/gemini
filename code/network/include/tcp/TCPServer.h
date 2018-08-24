#ifndef GEMINI_NETWORK_TCPServer_INCLUDE
#define GEMINI_NETWORK_TCPServer_INCLUDE
#include <boost/asio.hpp>
#include "../Server.h"

namespace gemini {

class TCPServerConnection;
class TCPServer : public Server {
 protected:
  typedef boost::asio::io_service service_type;
  typedef boost::asio::ip::tcp::acceptor acceptor_type;

 public:
  TCPServer();
  virtual ~TCPServer();

  /**
   * @brief 启动TCP服务
   *
   * @return Boolean
   */
  virtual Boolean start();

  /**
   * @brief 停止TCP服务。
   *
   */
  virtual void stop();

 protected:
  virtual std::shared_ptr<TCPServerConnection> createConnection();

 private:
  void async_accept();
  void handle_accept(std::shared_ptr<TCPServerConnection> conn,
                     const boost::system::error_code& error);

 private:
  MT_Boolean _isClose;

  boost::asio::io_service _ios;
  acceptor_type _acceptor;
  boost::asio::signal_set _signals;
};

}  // namespace gemini

#endif  // GEMINI_NETWORK_TCPServer_INCLUDE
