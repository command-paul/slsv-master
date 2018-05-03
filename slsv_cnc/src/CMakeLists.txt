SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/slsv)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

SET(BUILD_SWIG FALSE)

FIND_PACKAGE(SWIG REQUIRED)
#if (${BUILD_SWIG} EQUAL TRUE )
include(UseSWIG)
INCLUDE_DIRECTORIES(/usr/include/python3.6)
#INCLUDE_DIRECTORIES(.src)
FIND_PACKAGE(PythonLibs)
SET(CMAKE_SWIG_FLAGS "-DSWIGWORDSIZE64")
SET(CMAKE_SWIG_OUTDIR ${CMAKE_BINARY_DIR}/slsv)
SET(SWIG_OUTFILE_DIR "./" )


set(RISCV $ENV{RISCV})
INCLUDE_DIRECTORIES(${RISCV}/include/)
INCLUDE_DIRECTORIES(${RISCV}/lib)
INCLUDE_DIRECTORIES(Interface/SpikeSlsvIntreface/)
INCLUDE_DIRECTORIES(${RISCV}/include/spike)
link_directories(${RISCV}/lib)


SET_SOURCE_FILES_PROPERTIES(slsv_framework.i PROPERTIES CPLUSPLUS ON)
SET_SOURCE_FILES_PROPERTIES(slsv_framework.i PROPERTIES SWIG_FLAGS "-includeall")
SWIG_ADD_LIBRARY(slsv_framework LANGUAGE python SOURCES slsv_framework.i DeviceInstance.cpp BasicDeviceTests.cpp LockStepVerification.cpp traceCache.cpp)
#SWIG_ADD_MODULE(slsv_target python ./Device.i ./DeviceInstance.cpp)
SWIG_LINK_LIBRARIES(slsv_framework ${PYTHON_LIBRARIES} Interface State Coverage riscv spike_main fesvr )

#endif(${BUILD_SWIG} EQUAL TRUE )

#target_include_directories (slsv_framework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${RISCV}/include) # Specify the header files here
add_library (slsv_framework SHARED DeviceInstance.cpp BasicDeviceTests.cpp LockStepVerification.cpp traceCache.cpp)
#target_include_directories (Interface PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${RISCV}/include)
#target_include_directories (Interface PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${RISCV}/include slsvSpikeIf)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=gnu++0x")
target_include_directories (slsv_framework PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${RISCV}/include) # Specify the header files here