
add_library (State State.cpp)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")

target_include_directories (State PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})