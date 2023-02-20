cmake_minimum_required(VERSION 3.24)
project(Chapter4)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Chapter4 main.cpp)
target_link_libraries(Chapter4 ${OpenCV_LIBS})
