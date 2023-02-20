cmake_minimum_required(VERSION 3.24)
project(Chapter2)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Chapter2 main.cpp)
target_link_libraries(Chapter2 ${OpenCV_LIBS})
