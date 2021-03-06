#ifndef GEMINI_NETWORK_TCPServer_INCLUDE
#define GEMINI_NETWORK_TCPServer_INCLUDE
#include "../Server.h"
#include <boost/asio.hpp>

namespace gemini {

class TCPServerConnection;
class TCPServer : public Server
{
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
	void handle_accept(std::shared_ptr<TCPServerConnection> conn, const boost::system::error_code& error);

private:
	Boolean _isClose;

	boost::asio::io_service _ios;
	acceptor_type _acceptor;
	boost::asio::signal_set _signals;
};

}

#endif // GEMINI_NETWORK_TCPServer_INCLUDE
