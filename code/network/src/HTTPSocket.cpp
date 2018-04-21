#include "../include/HTTPSocket.h"

namespace gemini {

HTTPSocket::HTTPSocket(service_type& ios, TCPConnection* conn, Int hbTimeout)
	: Socket(ios, conn, hbTimeout)
{

}

HTTPSocket::~HTTPSocket()
{

}

void HTTPSocket::do_read() {
	using namespace boost::beast;

	// Read a request
	http::async_read(getSocket(), _buffer, _req,
		boost::asio::bind_executor(
			getStrand(),
			std::bind(
				&HTTPSocket::on_read,
				ddddddd<HTTPSocket>(),
				std::placeholders::_1,
				std::placeholders::_2)));
}

void HTTPSocket::on_read(boost::system::error_code ec, std::size_t bytes_transferred) {
	using namespace boost::beast;
	boost::ignore_unused(bytes_transferred);

	// This means they closed the connection
	if (ec == http::error::end_of_stream || ec == boost::asio::error::eof ||
		ec == boost::asio::error::connection_aborted || ec == boost::asio::error::connection_reset ||
		ec == boost::asio::error::connection_refused || ec == boost::asio::error::network_down ||
		ec == boost::asio::error::network_reset || ec == boost::asio::error::network_unreachable ||
		ec == boost::asio::error::not_connected || ec == boost::asio::error::shut_down) {
		return stop();
	}

	if (ec)
		return fail(ec, "read");

	// handle the request
	const http::verb method = _req.method();
	switch (method)
	{
	case http::verb::head:
		handle_head();
		break;
	case http::verb::get:
		handle_get();
		break;
	case http::verb::post:
		handle_post();
		break;
	case http::verb::put:
		handle_put();
		break;
	case http::verb::delete_:
		handle_delete();
		break;
	case http::verb::options:
		handle_options();
		break;
	default:
		break;
	}
}

void HTTPSocket::on_write(boost::system::error_code ec, std::size_t bytes_transferred, bool close) {
	boost::ignore_unused(bytes_transferred);

	if (ec)
		return fail(ec, "write");

	if (close)
	{
		// This means we should close the connection, usually because
		// the response indicated the "Connection: close" semantic.
		return stop();
	}

	// We're done with the response so delete it
	_res = nullptr;

	// Read another request
	do_read();
}

void HTTPSocket::fail(boost::system::error_code ec, char const * what) {
}

void HTTPSocket::handle_head() {
}

void HTTPSocket::handle_get() {
	using namespace boost::beast;

	// Attempt to open the file
	boost::beast::error_code ec;
	http::file_body::value_type body;
	body.open(_req.target().to_string().c_str(), boost::beast::file_mode::scan, ec);

	// Respond to GET request
	http::response<http::file_body> res{
		std::piecewise_construct,
		std::make_tuple(std::move(body)),
		std::make_tuple(http::status::ok, _req.version()) };
	res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
	res.set(http::field::content_type, mime_type(_req.target()));
	res.content_length(body.size());
	res.keep_alive(_req.keep_alive());
	send_lambda(*this)(std::move(res));
}

void HTTPSocket::handle_post() {
	using namespace boost::beast;
}

void HTTPSocket::handle_put() {

}

void HTTPSocket::handle_delete() {

}

void HTTPSocket::handle_options() {

}

boost::beast::string_view HTTPSocket::mime_type(const boost::beast::string_view & path) {
	using boost::beast::iequals;
	auto const ext = [&path]
	{
		auto const pos = path.rfind(".");
		if (pos == boost::beast::string_view::npos)
			return boost::beast::string_view{};
		return path.substr(pos);
	}();
	if (iequals(ext, ".htm"))  return "text/html";
	if (iequals(ext, ".html")) return "text/html";
	if (iequals(ext, ".php"))  return "text/html";
	if (iequals(ext, ".css"))  return "text/css";
	if (iequals(ext, ".txt"))  return "text/plain";
	if (iequals(ext, ".js"))   return "application/javascript";
	if (iequals(ext, ".json")) return "application/json";
	if (iequals(ext, ".xml"))  return "application/xml";
	if (iequals(ext, ".swf"))  return "application/x-shockwave-flash";
	if (iequals(ext, ".flv"))  return "video/x-flv";
	if (iequals(ext, ".png"))  return "image/png";
	if (iequals(ext, ".jpe"))  return "image/jpeg";
	if (iequals(ext, ".jpeg")) return "image/jpeg";
	if (iequals(ext, ".jpg"))  return "image/jpeg";
	if (iequals(ext, ".gif"))  return "image/gif";
	if (iequals(ext, ".bmp"))  return "image/bmp";
	if (iequals(ext, ".ico"))  return "image/vnd.microsoft.icon";
	if (iequals(ext, ".tiff")) return "image/tiff";
	if (iequals(ext, ".tif"))  return "image/tiff";
	if (iequals(ext, ".svg"))  return "image/svg+xml";
	if (iequals(ext, ".svgz")) return "image/svg+xml";
	return "application/text";
}

boost::beast::http::response<boost::beast::http::string_body> HTTPSocket::bad_request(boost::beast::string_view why)
{
	using namespace boost::beast;
	http::response<http::string_body> res{ http::status::bad_request, _req.version() };
	res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
	res.set(http::field::content_type, mime_type(_req.target()));
	res.keep_alive(_req.keep_alive());
	res.body() = why.to_string();
	res.prepare_payload();
	return res;
}

boost::beast::http::response<boost::beast::http::string_body> HTTPSocket::not_found(boost::beast::string_view target)
{
	using namespace boost::beast;
	http::response<http::string_body> res{ http::status::not_found, _req.version() };
	res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
	res.set(http::field::content_type, mime_type(_req.target()));
	res.keep_alive(_req.keep_alive());
	res.body() = "The resource '" + target.to_string() + "' was not found.";
	res.prepare_payload();
	return res;
}

boost::beast::http::response<boost::beast::http::string_body> HTTPSocket::server_error(boost::beast::string_view what)
{
	using namespace boost::beast;
	http::response<http::string_body> res{ http::status::internal_server_error, _req.version() };
	res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
	res.set(http::field::content_type, mime_type(_req.target()));
	res.keep_alive(_req.keep_alive());
	res.body() = "An error occurred: '" + what.to_string() + "'";
	res.prepare_payload();
	return res;
}

}
