
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/slsv)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=gnu++0x")  # -fsanitize=address 
add_executable(test Tests.cpp)
target_link_libraries (test LINK_PUBLIC slsv_framework State Interface Coverage)

add_executable(bst testBasicSelfTest.cpp)
target_link_libraries (bst LINK_PUBLIC slsv_framework State Interface Coverage)