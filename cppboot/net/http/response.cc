#include "cppboot/net/http/response.h"

#include <string>

namespace cppboot {
namespace http {

namespace status_strings {

const std::string ok = "HTTP/1.0 200 OK\r\n";
const std::string created = "HTTP/1.0 201 Created\r\n";
const std::string accepted = "HTTP/1.0 202 Accepted\r\n";
const std::string no_content = "HTTP/1.0 204 No Content\r\n";
const std::string multiple_choices = "HTTP/1.0 300 Multiple Choices\r\n";
const std::string moved_permanently = "HTTP/1.0 301 Moved Permanently\r\n";
const std::string moved_temporarily = "HTTP/1.0 302 Moved Temporarily\r\n";
const std::string not_modified = "HTTP/1.0 304 Not Modified\r\n";
const std::string bad_request = "HTTP/1.0 400 Bad Request\r\n";
const std::string unauthorized = "HTTP/1.0 401 Unauthorized\r\n";
const std::string forbidden = "HTTP/1.0 403 Forbidden\r\n";
const std::string not_found = "HTTP/1.0 404 Not Found\r\n";
const std::string internal_server_error =
    "HTTP/1.0 500 Internal Server Error\r\n";
const std::string not_implemented = "HTTP/1.0 501 Not Implemented\r\n";
const std::string bad_gateway = "HTTP/1.0 502 Bad Gateway\r\n";
const std::string service_unavailable = "HTTP/1.0 503 Service Unavailable\r\n";

asio::const_buffer to_buffer(Response::status_type status) {
  switch (status) {
    case Response::ok:
      return asio::buffer(ok);
    case Response::created:
      return asio::buffer(created);
    case Response::accepted:
      return asio::buffer(accepted);
    case Response::no_content:
      return asio::buffer(no_content);
    case Response::multiple_choices:
      return asio::buffer(multiple_choices);
    case Response::moved_permanently:
      return asio::buffer(moved_permanently);
    case Response::moved_temporarily:
      return asio::buffer(moved_temporarily);
    case Response::not_modified:
      return asio::buffer(not_modified);
    case Response::bad_request:
      return asio::buffer(bad_request);
    case Response::unauthorized:
      return asio::buffer(unauthorized);
    case Response::forbidden:
      return asio::buffer(forbidden);
    case Response::not_found:
      return asio::buffer(not_found);
    case Response::internal_server_error:
      return asio::buffer(internal_server_error);
    case Response::not_implemented:
      return asio::buffer(not_implemented);
    case Response::bad_gateway:
      return asio::buffer(bad_gateway);
    case Response::service_unavailable:
      return asio::buffer(service_unavailable);
    default:
      return asio::buffer(internal_server_error);
  }
}

}  // namespace status_strings

namespace misc_strings {

const char name_value_separator[] = {':', ' '};
const char crlf[] = {'\r', '\n'};

}  // namespace misc_strings

std::vector<asio::const_buffer> Response::to_buffers() {
  std::vector<asio::const_buffer> buffers;
  buffers.push_back(status_strings::to_buffer(status));
  for (std::size_t i = 0; i < headers.size(); ++i) {
    Header& h = headers[i];
    buffers.push_back(asio::buffer(h.name));
    buffers.push_back(asio::buffer(misc_strings::name_value_separator));
    buffers.push_back(asio::buffer(h.value));
    buffers.push_back(asio::buffer(misc_strings::crlf));
  }
  buffers.push_back(asio::buffer(misc_strings::crlf));
  buffers.push_back(asio::buffer(content));
  return buffers;
}

namespace stock_replies {

const char ok[] = "";
const char created[] =
    "<html>"
    "<head><title>Created</title></head>"
    "<body><h1>201 Created</h1></body>"
    "</html>";
const char accepted[] =
    "<html>"
    "<head><title>Accepted</title></head>"
    "<body><h1>202 Accepted</h1></body>"
    "</html>";
const char no_content[] =
    "<html>"
    "<head><title>No Content</title></head>"
    "<body><h1>204 Content</h1></body>"
    "</html>";
const char multiple_choices[] =
    "<html>"
    "<head><title>Multiple Choices</title></head>"
    "<body><h1>300 Multiple Choices</h1></body>"
    "</html>";
const char moved_permanently[] =
    "<html>"
    "<head><title>Moved Permanently</title></head>"
    "<body><h1>301 Moved Permanently</h1></body>"
    "</html>";
const char moved_temporarily[] =
    "<html>"
    "<head><title>Moved Temporarily</title></head>"
    "<body><h1>302 Moved Temporarily</h1></body>"
    "</html>";
const char not_modified[] =
    "<html>"
    "<head><title>Not Modified</title></head>"
    "<body><h1>304 Not Modified</h1></body>"
    "</html>";
const char bad_request[] =
    "<html>"
    "<head><title>Bad Request</title></head>"
    "<body><h1>400 Bad Request</h1></body>"
    "</html>";
const char unauthorized[] =
    "<html>"
    "<head><title>Unauthorized</title></head>"
    "<body><h1>401 Unauthorized</h1></body>"
    "</html>";
const char forbidden[] =
    "<html>"
    "<head><title>Forbidden</title></head>"
    "<body><h1>403 Forbidden</h1></body>"
    "</html>";
const char not_found[] =
    "<html>"
    "<head><title>Not Found</title></head>"
    "<body><h1>404 Not Found</h1></body>"
    "</html>";
const char internal_server_error[] =
    "<html>"
    "<head><title>Internal Server Error</title></head>"
    "<body><h1>500 Internal Server Error</h1></body>"
    "</html>";
const char not_implemented[] =
    "<html>"
    "<head><title>Not Implemented</title></head>"
    "<body><h1>501 Not Implemented</h1></body>"
    "</html>";
const char bad_gateway[] =
    "<html>"
    "<head><title>Bad Gateway</title></head>"
    "<body><h1>502 Bad Gateway</h1></body>"
    "</html>";
const char service_unavailable[] =
    "<html>"
    "<head><title>Service Unavailable</title></head>"
    "<body><h1>503 Service Unavailable</h1></body>"
    "</html>";

std::string to_string(Response::status_type status) {
  switch (status) {
    case Response::ok:
      return ok;
    case Response::created:
      return created;
    case Response::accepted:
      return accepted;
    case Response::no_content:
      return no_content;
    case Response::multiple_choices:
      return multiple_choices;
    case Response::moved_permanently:
      return moved_permanently;
    case Response::moved_temporarily:
      return moved_temporarily;
    case Response::not_modified:
      return not_modified;
    case Response::bad_request:
      return bad_request;
    case Response::unauthorized:
      return unauthorized;
    case Response::forbidden:
      return forbidden;
    case Response::not_found:
      return not_found;
    case Response::internal_server_error:
      return internal_server_error;
    case Response::not_implemented:
      return not_implemented;
    case Response::bad_gateway:
      return bad_gateway;
    case Response::service_unavailable:
      return service_unavailable;
    default:
      return internal_server_error;
  }
}

}  // namespace stock_replies

Response Response::stock_reply(Response::status_type status) {
  Response rep;
  rep.status = status;
  rep.content = stock_replies::to_string(status);
  rep.set_header("Content-Length", std::to_string(rep.content.size()));
  rep.set_header("Content-Type", "text/html");
  return rep;
}

std::string Response::header(const std::string& name) noexcept {
  for (auto& i : headers) {
    if (i.name == name) {
      return i.value;
    }
  }
  return {};
}

// TODO: duplicate
void Response::set_header(const std::string& name,
                          const std::string& value) noexcept {
  for (auto& i : headers) {
    if (i.name == name) {
      i.value = value;
      return;
    }
  }

  Header h = {name, value};
  headers.push_back(h);
}

void Response::WriteText(status_type code, const std::string& body) {
  status = code;
  content = body;
  set_header("Content-Length", std::to_string(content.size()));
  set_header("Content-Type", "text/plain");
}

void Response::WriteHtml(status_type code, const std::string& body) {
  status = code;
  content = body;
  set_header("Content-Length", std::to_string(content.size()));
  set_header("Content-Type", "text/html");
}

void Response::WriteJson(status_type code, const json& body) {
  status = code;
  content = body.dump();
  set_header("Content-Length", std::to_string(content.size()));
  set_header("Content-Type", "application/json");
}

}  // namespace http
}  // namespace cppboot
