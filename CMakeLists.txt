cmake_minimum_required(VERSION 3.10)
project(byol C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
add_executable(byol src/main.c src/parsing.c src/util.c ../lib/mpc.c src/parsing.h src/eval.c src/eval.h)