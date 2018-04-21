#include "../../include/tcp/TCPServer.h"
#include "../../include/IOServicePool.h"
#include "../../public/tcp/TCPServerConnection.h"

namespace gemini {

using namespace boost::asio;
TCPServer::TCPServer()
	: _acceptor(_ios, ip::tcp::endpoint(ip::tcp::v4(), 16890))
	//, m_acceptor(m_ioservice, ip::tcp::endpoint(ip::address_v4::from_string("192.168.0.95"), 16890))
	, _signals(_ios)
{
	_isClose = true;
	_acceptor.set_option(ip::tcp::acceptor::reuse_address(true));
	boost::system::error_code ec;
	_acceptor.listen(boost::asio::socket_base::max_listen_connections, ec);

	_signals.add(SIGINT);
	_signals.add(SIGTERM);
#if defined(SIGQUIT)  
	m_signals.add(SIGQUIT);
#endif  
	_signals.async_wait(std::bind(&TCPServer::stop, this));
}

TCPServer::~TCPServer()
{

}

Boolean TCPServer::start() {
	_isClose = false;
	if (!_acceptor.is_open()) {
		return false;
	}
	
	IOServicePool::instance().start();
	async_accept();
	_ios.run();
	return true;
}

void TCPServer::stop() {
	_isClose = true;
	_acceptor.close();
	_ios.stop();
	IOServicePool::instance().stop();
}

std::shared_ptr<TCPServerConnection> TCPServer::createConnection() {
	return std::shared_ptr<TCPServerConnection>(new TCPServerConnection());
}

void TCPServer::async_accept() {
	std::shared_ptr<TCPServerConnection> conn = createConnection();
	conn->bindIOS(IOServicePool::instance().get_io_service());
	_acceptor.async_accept(conn->get()->getSocket(),
		boost::bind(&TCPServer::handle_accept, this, conn, boost::asio::placeholders::error));
}

void TCPServer::handle_accept(std::shared_ptr<TCPServerConnection> conn, const boost::system::error_code & error) {
	if (error || _isClose)
		return;

	conn->get()->start();
	async_accept();
}

}