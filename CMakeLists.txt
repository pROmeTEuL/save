cmake_minimum_required(VERSION 3.0)

project(save LANGUAGES C)

add_executable(save main.c copy.c copy.h)

install(TARGETS save RUNTIME DESTINATION bin)
