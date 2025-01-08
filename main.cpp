#include <asio.hpp>
#include <iostream>
#include <string>

const std::string content = R"html(

<!DOCTYPE html>
<html>
  <body>Hello, world!</body>
</html>

)html";

int main() {
  try {
    using asio::ip::tcp;

    asio::io_context io_context;
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));

    for (;;) {
      tcp::socket socket(io_context);
      acceptor.accept(socket);

      std::string http_message =
          "HTTP/1.1 200 OK\n"
          "Content-Type: text/html\n" +
          ("Content-Length:" + std::to_string(content.length()) + "\n\n") +
          content;

      asio::write(socket, asio::buffer(http_message));
    }
  } catch (std::exception &e) {
    std::cerr << e.what();
  }
}