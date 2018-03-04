# This will NOT be wrapped by swig for now

SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(testTelnet Telnet.cpp libtelnet.cpp)
add_library (Telnet Telnet.cpp libtelnet.cpp)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 ")
target_include_directories (Telnet PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})