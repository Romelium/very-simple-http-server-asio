#include <asio.hpp>
#include <asio/write.hpp>
#include <cstdio>
#include <fmt/base.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <string>

using asio::ip::tcp;

int main(int argc, char *argv[]) {
  try {
    asio::io_context io_context;
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));

    for (;;) {
      tcp::socket socket(io_context);
      acceptor.accept(socket);

      const std::string content = "Hello World!";

      std::error_code ignored_error;
      std::string http_message = fmt::format("HTTP/1.1 200 OK\n"
                                             "Content-Type: text/plain\n"
                                             "Content-Length: {}\n"
                                             "\n"
                                             "{}",
                                             content.length(), content);

      asio::write(socket, asio::buffer(http_message));
    }
  } catch (std::exception &e) {
    fmt::println(stderr, "{}", e.what());
  }
}