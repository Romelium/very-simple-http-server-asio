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

std::string make_daytime_string() {
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  char buffer[26];
  ctime_s(buffer, sizeof(buffer), &now);
  std::string output(buffer);
  return buffer;
}

int main(int argc, char *argv[]) {
  try {
    asio::io_context io_context;
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 13));

    for (;;) {
      tcp::socket socket(io_context);
      acceptor.accept(socket);
      std::string message = make_daytime_string();

      std::error_code ignored_error;
      asio::write(socket, asio::buffer(message), ignored_error);
    }
  } catch (std::exception &e) {
    fmt::println(stderr, "{}", e.what());
  }
}