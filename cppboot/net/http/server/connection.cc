#include "cppboot/net/http/server/connection.h"

#include <tuple>
#include <algorithm>

#include "cppboot/net/http/server/connection_manager.h"

namespace cppboot {
namespace http {
TcpConnection::TcpConnection(asio::ip::tcp::socket socket,
                             ConnectionManager& manager, ServeMux& handler)
    : socket_(std::move(socket)),
      connection_manager_(manager),
      request_handler_(handler) {}

void TcpConnection::Start() { DoRead(); }

void TcpConnection::Stop() { socket_.close(); }

void TcpConnection::DoRead() {
  auto self(shared_from_this());
  socket_.async_read_some(
      asio::buffer(buffer_),
      [this, self](std::error_code ec, std::size_t bytes_transferred) {
        if (!ec) {
          RequestParser::result_type result;
          std::tie(result, std::ignore) = request_parser_.parse(
              request_, buffer_.data(), buffer_.data() + bytes_transferred);

          if (result == RequestParser::good) {
            request_handler_.ServeHttp(request_, &reply_);
            DoWrite();
          } else if (result == RequestParser::bad) {
            reply_ = Response::stock_reply(Response::bad_request);
            DoWrite();
          } else {
            DoRead();
          }
        } else if (ec != asio::error::operation_aborted) {
          connection_manager_.Stop(shared_from_this());
        }
      });
}

void TcpConnection::DoWrite() {
  auto self(shared_from_this());
  asio::async_write(socket_, reply_.to_buffers(),
                    [this, self](std::error_code ec, std::size_t) {
                      if (!ec) {
                        // Initiate graceful connection closure.
                        asio::error_code ignored_ec;
                        socket_.shutdown(asio::ip::tcp::socket::shutdown_both,
                                         ignored_ec);
                      }

                      if (ec != asio::error::operation_aborted) {
                        connection_manager_.Stop(shared_from_this());
                      }
                    });
}

}  // namespace http
}  // namespace cppboot