SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/slsv)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(RISCV $ENV{RISCV})

INCLUDE_DIRECTORIES(${RISCV}/include/)
INCLUDE_DIRECTORIES(${RISCV}/lib)
INCLUDE_DIRECTORIES(${RISCV}/include/spike)

link_directories(${RISCV}/lib)

# This will NOT be wrapped by swig for now

add_library (slsvSpikeIf SHARED SpikeIf.cpp)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++11")

target_include_directories (slsvSpikeIf PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${RISCV}/include) # Specify the header files here
target_link_libraries(slsvSpikeIf riscv spike_main fesvr State Interface Coverage slsv_framework) ## link to the shared object files here 
#target_include_directories (testSpikeIf PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${RISCV}/include) # Specify the header files here
#target_link_libraries(testSpikeIf riscv spike_main fesvrState Interface Coverage slsv_framework ) 
# TDD On V0 Interface