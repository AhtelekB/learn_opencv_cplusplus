cmake_minimum_required(VERSION 3.24)
project(Chapter8)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Chapter8 main.cpp)
target_link_libraries(Chapter8 ${OpenCV_LIBS})
