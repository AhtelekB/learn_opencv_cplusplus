cmake_minimum_required(VERSION 3.24)
project(Project3)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(Project3 main.cpp)
target_link_libraries(Project3 ${OpenCV_LIBS})