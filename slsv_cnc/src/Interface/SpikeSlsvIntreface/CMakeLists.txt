project(SpikeIf)
cmake_minimum_required(VERSION 3.1)
SET(CMAKE_BINARY_DIR ./ )
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(RISCV $ENV{RISCV})
INCLUDE_DIRECTORIES(${RISCV}/include/)
INCLUDE_DIRECTORIES(${RISCV}/lib)
INCLUDE_DIRECTORIES(${RISCV}/include/spike)

link_directories(${RISCV}/lib)

add_library (slsvSpikeIf SHARED SpikeIf.cpp Interface.cpp)
add_executable(testSpikeIf Test.cpp SpikeIf.cpp Interface.cpp )

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++11")

target_include_directories (slsvSpikeIf PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${RISCV}/include) # Specify the header files here
target_link_libraries(slsvSpikeIf riscv spike_main fesvr) ## link to the shared object files here 
target_include_directories (testSpikeIf PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${RISCV}/include) # Specify the header files here
target_link_libraries(testSpikeIf riscv spike_main fesvr) 
# TDD On V0 Interface

