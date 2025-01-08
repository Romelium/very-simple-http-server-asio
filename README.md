# Introduction

This is a simple HTTP server using the Asio library in C++. The server listens on port 8080. The code without the html content is only 28 lines long.

## Purpose

This is meant to showcase how minimal you can make an HTTP server at a near barebone level while being cross-platform. It also shows what to include to add an basic HTTP server to your project.

## Note

- This assumes you know how to build a CMake project.
- Make sure you use the **CMakePresets.json**, have **ninja** build system installed, and **VCPKG_ROOT** environment variable set. If you don't know what they are, just google them.
