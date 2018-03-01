
cmake_minimum_required(VERSION 2.6)

project(SLSV)
add_subdirectory(src/State)
add_subdirectory(src/Interface)
SET (CMAKE_BINARY_DIR "./")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
add_executable(build ./src/Tests.cpp)

target_link_libraries (build LINK_PUBLIC State)
message(WARNING,"RUN THIS THROUGH THE INTEL PS FOR MEM LEAKS !!!")
message(WARNING,"SWIG Template variable naming is poor please Rework !!!")