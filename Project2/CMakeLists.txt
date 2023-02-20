cmake_minimum_required(VERSION 3.24)
project(Project2)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Project2 main.cpp)
target_link_libraries(Project2 ${OpenCV_LIBS})