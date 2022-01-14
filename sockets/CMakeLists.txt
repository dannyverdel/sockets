cmake_minimum_required(VERSION 3.20)
project(sockets C)

set(CMAKE_C_STANDARD 99)

add_executable(sockets main.c)
add_executable(client client.c)
add_executable(server server.c)
