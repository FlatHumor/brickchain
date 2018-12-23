cmake_minimum_required(VERSION 3.12)
project(brickchain)

set(CMAKE_CXX_STANDARD 11)

add_executable(brickchain main.cpp brick.cpp brick.h transaction.cpp transaction.h brick_chain.cpp brick_chain.h chain.h repository.h file_repository.cpp file_repository.h)