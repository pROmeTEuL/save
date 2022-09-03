cmake_minimum_required(VERSION 3.0)

project(save LANGUAGES C)

add_executable(save main.c)

install(TARGETS save RUNTIME DESTINATION bin)
