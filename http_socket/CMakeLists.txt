cmake_minimum_required(VERSION 3.20)
project(http_socket C)

set(CMAKE_C_STANDARD 99)

add_executable(server server.c)
add_executable(client client.c)