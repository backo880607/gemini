#ifndef GEMINI_NETWORK_HTTPServerSocket_INCLUDE
#define GEMINI_NETWORK_HTTPServerSocket_INCLUDE
#include "../Socket.h"
#include <boost\beast.hpp>

namespace gemini {

class HTTPServerSocket : public Socket
{
public:
	HTTPServerSocket(service_type& ios, TCPConnection* conn, UInt hbTimeout);
	~HTTPServerSocket();

protected:
	virtual void do_read();

private:
	void on_read(boost::system::error_code ec, std::size_t bytes_transferred);

private:
	const std::string _doc_root;
	boost::beast::flat_buffer _buffer;
	boost::beast::http::request<boost::beast::http::string_body> _req;
	std::shared_ptr<void> _res;

	boost::asio::strand<
		boost::asio::io_context::executor_type> strand_;
};

}
#endif // !GEMINI_NETWORK_HTTPServerSocket_INCLUDE
