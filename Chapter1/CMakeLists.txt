cmake_minimum_required(VERSION 3.24)
project(Chapter1)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUED_DIRS})

add_executable(Chapter1 main.cpp)
target_link_libraries(Chapter1 ${OpenCV_LIBS})
