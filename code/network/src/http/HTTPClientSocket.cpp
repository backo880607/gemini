#include "../../include/http/HTTPServerSocket.h"

namespace gemini {

boost::beast::string_view
mime_type(boost::beast::string_view path)
{
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

// Append an HTTP rel-path to a local filesystem path.
// The returned path is normalized for the platform.
std::string
path_cat(
	boost::beast::string_view base,
	boost::beast::string_view path)
{
	if (base.empty())
		return path.to_string();
	std::string result = base.to_string();
#if BOOST_MSVC
	char constexpr path_separator = '\\';
	if (result.back() == path_separator)
		result.resize(result.size() - 1);
	result.append(path.data(), path.size());
	for (auto& c : result)
		if (c == '/')
			c = path_separator;
#else
	char constexpr path_separator = '/';
	if (result.back() == path_separator)
		result.resize(result.size() - 1);
	result.append(path.data(), path.size());
#endif
	return result;
}

// This function produces an HTTP response for the given
// request. The type of the response object depends on the
// contents of the request, so the interface requires the
// caller to pass a generic lambda for receiving the response.
template<
	class Body, class Allocator,
	class Send>
	void
	handle_request(
		boost::beast::string_view doc_root,
		boost::beast::http::request<Body, boost::beast::http::basic_fields<Allocator>>&& req,
		Send&& send)
{
	using namespace boost::beast;

	// Returns a bad request response
	auto const bad_request =
		[&req](boost::beast::string_view why)
	{
		http::response<http::string_body> res{ http::status::bad_request, req.version() };
		res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
		res.set(http::field::content_type, "text/html");
		res.keep_alive(req.keep_alive());
		res.body() = why.to_string();
		res.prepare_payload();
		return res;
	};

	// Returns a not found response
	auto const not_found =
		[&req](boost::beast::string_view target)
	{
		http::response<http::string_body> res{ http::status::not_found, req.version() };
		res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
		res.set(http::field::content_type, "text/html");
		res.keep_alive(req.keep_alive());
		res.body() = "The resource '" + target.to_string() + "' was not found.";
		res.prepare_payload();
		return res;
	};

	// Returns a server error response
	auto const server_error =
		[&req](boost::beast::string_view what)
	{
		http::response<http::string_body> res{ http::status::internal_server_error, req.version() };
		res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
		res.set(http::field::content_type, "text/html");
		res.keep_alive(req.keep_alive());
		res.body() = "An error occurred: '" + what.to_string() + "'";
		res.prepare_payload();
		return res;
	};

	// Make sure we can handle the method
	if (req.method() != http::verb::get &&
		req.method() != http::verb::head)
		return send(bad_request("Unknown HTTP-method"));

	// Request path must be absolute and not contain "..".
	if (req.target().empty() ||
		req.target()[0] != '/' ||
		req.target().find("..") != boost::beast::string_view::npos)
		return send(bad_request("Illegal request-target"));

	// Build the path to the requested file
	std::string path = path_cat(doc_root, req.target());
	if (req.target().back() == '/')
		path.append("index.html");

	// Attempt to open the file
	boost::beast::error_code ec;
	http::file_body::value_type body;
	body.open(path.c_str(), boost::beast::file_mode::scan, ec);

	// Handle the case where the file doesn't exist
	if (ec == boost::system::errc::no_such_file_or_directory)
		return send(not_found(req.target()));

	// Handle an unknown error
	if (ec)
		return send(server_error(ec.message()));

	// Respond to HEAD request
	if (req.method() == http::verb::head)
	{
		http::response<http::empty_body> res{ http::status::ok, req.version() };
		res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
		res.set(http::field::content_type, mime_type(path));
		res.content_length(body.size());
		res.keep_alive(req.keep_alive());
		return send(std::move(res));
	}

	// Respond to GET request
	http::response<http::file_body> res{
		std::piecewise_construct,
		std::make_tuple(std::move(body)),
		std::make_tuple(http::status::ok, req.version()) };
	res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
	res.set(http::field::content_type, mime_type(path));
	res.content_length(body.size());
	res.keep_alive(req.keep_alive());
	return send(std::move(res));
}

// This is the C++11 equivalent of a generic lambda.
// The function object is used to send an HTTP message.
struct send_lambda
{
	HTTPServerSocket& self_;

	explicit
		send_lambda(HTTPServerSocket& self)
		: self_(self)
	{
	}

	template<bool isRequest, class Body, class Fields>
	void
		operator()(boost::beast::http::message<isRequest, Body, Fields>&& msg) const
	{
		using namespace boost::beast;
		// The lifetime of the message has to extend
		// for the duration of the async operation so
		// we use a shared_ptr to manage it.
		auto sp = std::make_shared<
			http::message<isRequest, Body, Fields>>(std::move(msg));

		// Store a type-erased version of the shared
		// pointer in the class to keep it alive.
		//self_._res = sp;

		// Write the response
		/*http::async_write(
			self_.getSocket(),
			*sp,
			boost::asio::bind_executor(
				self_.getStrand(),
				std::bind(
					&session::on_write,
					self_.shared_from_this(),
					std::placeholders::_1,
					std::placeholders::_2,
					sp->need_eof())));*/
	}
};

HTTPServerSocket::HTTPServerSocket(service_type& ios, TCPConnection* conn, UInt hbTimeout)
	: Socket(ios, conn, hbTimeout)
	, strand_(getSocket().get_executor())
{

}

HTTPServerSocket::~HTTPServerSocket()
{

}

void HTTPServerSocket::do_read()
{
	using namespace boost::beast;
	http::async_read(getSocket(), _buffer, _req,
		boost::asio::bind_executor(
			strand_,
			boost::bind(
				&HTTPServerSocket::on_read,
				ddddddd<HTTPServerSocket>(),
				boost::placeholders::_1,
				boost::placeholders::_2)));
}

void HTTPServerSocket::on_read(boost::system::error_code ec, std::size_t bytes_transferred)
{
	using namespace boost::beast;

	// This means they closed the connection
	/*if (ec == http::error::end_of_stream)
		return do_close();

	if (ec)
		return fail(ec, "read");*/

	send_lambda lambda(*this);
	std::string target = _req.target().to_string();
	std::string value = _req.body();
	boost::beast::http::field::content_type;
	handle_request(_doc_root, std::move(_req), lambda);
}


}