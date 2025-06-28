cmake_minimum_required(VERSION 3.10)
project(delta)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(QUANTLIB REQUIRED QuantLib)

include_directories(${QUANTLIB_INCLUDE_DIRS})
link_directories(${QUANTLIB_LIBRARY_DIRS})

add_executable(delta_vanilla ../delta_vanilla.cpp)
target_link_libraries(delta_vanilla ${QUANTLIB_LIBRARIES})