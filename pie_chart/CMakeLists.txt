cmake_minimum_required(VERSION 3.6)
project(sinus)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

set(SOURCE_FILES main.c canvasimg/canvasimg.h canvasimg/tsimple.h canvasimg/canvasimg.c  )
add_executable(sinus ${SOURCE_FILES})