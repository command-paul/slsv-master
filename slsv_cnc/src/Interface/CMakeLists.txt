SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/slsv)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

SET(BUILD_SWIG TRUE)

FIND_PACKAGE(SWIG REQUIRED)
#if (${BUILD_SWIG} EQUAL TRUE )
include(UseSWIG)
INCLUDE_DIRECTORIES(/usr/include/python3.6)
INCLUDE_DIRECTORIES(.src/Interface)
FIND_PACKAGE(PythonLibs)
SET(CMAKE_SWIG_FLAGS "-DSWIGWORDSIZE64")
SET(SWIG_OUTFILE_DIR "./")
SET(CMAKE_SWIG_OUTDIR ${CMAKE_BINARY_DIR}/slsv)

SET_SOURCE_FILES_PROPERTIES(./Interface.i PROPERTIES CPLUSPLUS ON)
SET_SOURCE_FILES_PROPERTIES(./Interface.i PROPERTIES SWIG_FLAGS "-includeall")

set(RISCV $ENV{RISCV})
INCLUDE_DIRECTORIES(${RISCV}/include/)
INCLUDE_DIRECTORIES(./SpikeSlsvIntreface/)
INCLUDE_DIRECTORIES(${RISCV}/lib)
INCLUDE_DIRECTORIES(${RISCV}/include/spike)

link_directories(${RISCV}/lib)

#SWIG_ADD_LIBRARY(slsv_interface LANGUAGE python SOURCES ./Interface.i Interface.cpp ./V0/V0.cpp ./Telnet/Telnet.cpp ./Telnet/libtelnet.cpp ./SpikeSlsvIntreface/SpikeIf.cpp)
SWIG_ADD_LIBRARY(slsv_interface LANGUAGE python SOURCES ./Interface.i Interface.cpp )
SWIG_LINK_LIBRARIES(slsv_interface riscv spike_main fesvr slsv_framework State Telnet slsvSpikeIf ${PYTHON_LIBRARIES})
#endif(${BUILD_SWIG} EQUAL TRUE )
#add_library (Interface SHARED Interface.cpp ./V0/V0.cpp ./Telnet/Telnet.cpp ./Telnet/libtelnet.cpp)
add_library (Interface SHARED Interface.cpp ./V0/V0.cpp)

target_include_directories (Interface PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${RISCV}/include) # Specify the header files here
target_link_libraries(Interface riscv spike_main fesvr State Coverage slsv_framework Telnet slsvSpikeIf) ## link to the shared object files here 
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++11 ")

