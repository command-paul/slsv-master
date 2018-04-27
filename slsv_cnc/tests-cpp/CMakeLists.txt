
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/slsv)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(../src)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=gnu++0x")  # -fsanitize=address 
add_executable(testcpp Tests.cpp)
target_link_libraries (testcpp LINK_PUBLIC slsv_framework State Interface Coverage)



# The SlsvSpikeIf needs the following additional path includes
set(RISCV $ENV{RISCV})

INCLUDE_DIRECTORIES(${RISCV}/include/)
INCLUDE_DIRECTORIES(${RISCV}/lib)
INCLUDE_DIRECTORIES(${RISCV}/include/spike)


link_directories(${RISCV}/lib)

add_executable(bst testBasicSelfTest.cpp)
target_include_directories (bst PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${RISCV}/include) 
target_link_libraries (bst LINK_PUBLIC slsv_framework State Interface Coverage slsvSpikeIf)

add_executable(lsv testLockStepVerification.cpp)
target_include_directories (lsv PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${RISCV}/include) 
target_link_libraries (lsv LINK_PUBLIC slsv_framework State Interface Coverage slsvSpikeIf)
#target_link_libraries(testSpikeIf riscv spike_main fesvrState Interface Coverage slsv_framework ) 
