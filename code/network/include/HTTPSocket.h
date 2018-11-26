#ifndef GEMINI_NETWORK_HTTPSocket_INCLUDE
#define GEMINI_NETWORK_HttpSocket_INCLUDE
#include <boost\beast.hpp>
#include "Socket.h"

namespace gemini {
namespace network {

class HTTPSocket : public Socket {
  // This is the C++11 equivalent of a generic lambda.
  // The function object is used to send an HTTP message.
  struct send_lambda {
    HTTPSocket& self_;
    explicit send_lambda(HTTPSocket& self) : self_(self) {}

    template <bool isRequest, class Body, class Fields>
    void operator()(
        boost::beast::http::message<isRequest, Body, Fields>&& msg) const {
      // The lifetime of the message has to extend
      // for the duration of the async operation so
      // we use a shared_ptr to manage it.
      auto sp = std::make_shared<
          boost::beast::http::message<isRequest, Body, Fields>>(std::move(msg));

      // Store a type-erased version of the shared
      // pointer in the class to keep it alive.
      self_._res = sp;

      // Write the response
      boost::beast::http::async_write(
          self_.getSocket(), *sp,
          boost::asio::bind_executor(
              self_.getStrand(),
              std::bind(&HTTPSocket::on_write, self_.ddddddd<HTTPSocket>(),
                        std::placeholders::_1, std::placeholders::_2,
                        sp->need_eof())));
    }
  };

 public:
  HTTPSocket(service_type& ios, TCPConnection* conn, Int hbTimeout);
  ~HTTPSocket();

 protected:
  virtual void do_read();

 private:
  void on_read(boost::system::error_code ec, std::size_t bytes_transferred);
  void on_write(boost::system::error_code ec, std::size_t bytes_transferred,
                bool close);

  // Report a failure
  void fail(boost::system::error_code ec, char const* what);

  void handle_head();
  void handle_get();
  void handle_post();
  void handle_put();
  void handle_delete();
  void handle_options();

  boost::beast::string_view mime_type(const boost::beast::string_view& path);
  boost::beast::http::response<boost::beast::http::string_body> bad_request(
      boost::beast::string_view why);
  boost::beast::http::response<boost::beast::http::string_body> not_found(
      boost::beast::string_view target);
  boost::beast::http::response<boost::beast::http::string_body> server_error(
      boost::beast::string_view what);

 private:
  boost::beast::flat_buffer _buffer;
  boost::beast::http::request<boost::beast::http::string_body> _req;
  std::shared_ptr<void> _res;
};

}  // namespace network
}  // namespace gemini
#endif  // GEMINI_NETWORK_HttpSocket_INCLUDE
