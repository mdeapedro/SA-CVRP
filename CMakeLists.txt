cmake_minimum_required(VERSION 3.10)
project(SA-CVRP)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/bin)

add_executable(sa_cvrp src/main.c)

target_compile_options(sa_cvrp PRIVATE -Wall -Wextra)
