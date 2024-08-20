cmake_minimum_required(VERSION 3.30)
project(ray_tracing CXX)

set(CMAKE_CXX_COMPILER /usr/bin/clang++)
set(CMAKE_GENERATOR "Ninja")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV 4.10 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

aux_source_directory(src SRC_LIST)

add_executable(in_one_weekend ${SRC_LIST})
include_directories(include)
target_link_libraries(in_one_weekend PRIVATE ${OpenCV_LIBS})