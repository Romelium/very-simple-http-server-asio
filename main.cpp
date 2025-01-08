#include <algorithm>
#include <array>
#include <asio.hpp>
#include <cstdio>
#include <fmt/base.h>
#include <fmt/core.h>
#include <fmt/format.h>
#include <iostream>
#include <string>

using asio::ip::tcp;

int main(int argc, char *argv[]) {
  try {
    if (argc != 2) {
      fmt::println(stderr, "Usage: client <host>");
      return 1;
    }
    fmt::println("host: {}", argv[1]);
    asio::io_context io_context;
    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints = resolver.resolve(argv[1], "daytime");
    std::for_each(
        endpoints.begin(), endpoints.end(),
        [&](asio::ip::basic_resolver_entry<tcp> result) {
          const asio::ip::basic_endpoint<tcp> endpoint = result.endpoint();
          fmt::println("Endpoint Address: {} Port: {}",
                       endpoint.address().to_string(), endpoint.port());
        });

    tcp::socket socket(io_context);
    asio::connect(socket, endpoints);
    for (;;) {
      std::array<char, 128> buffer;
      std::error_code error;

      size_t len = socket.read_some(asio::buffer(buffer), error);
      if (error == asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw std::system_error(error); // Some other error.

      std::cout.write(buffer.data(), len);
    }
  } catch (std::exception &e) {
    fmt::println(stderr, "{}", e.what());
  }
}