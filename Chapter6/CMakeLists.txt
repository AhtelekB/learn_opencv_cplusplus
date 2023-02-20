cmake_minimum_required(VERSION 3.24)
project(Chapter6)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Chapter6 main.cpp)
target_link_libraries(Chapter6 ${OpenCV_LIBS})
