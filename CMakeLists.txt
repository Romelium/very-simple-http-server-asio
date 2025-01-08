cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(ProgramName)

find_package(fmt CONFIG REQUIRED)
find_package(asio CONFIG REQUIRED)

add_executable(ProgramName main.cpp)
add_executable(Server server.cpp)

target_link_libraries(ProgramName PRIVATE fmt::fmt asio::asio)
target_link_libraries(Server PRIVATE fmt::fmt asio::asio)