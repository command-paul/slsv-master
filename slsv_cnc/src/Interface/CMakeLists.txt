SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/slsv)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

SET(BUILD_SWIG FALSE)

FIND_PACKAGE(SWIG REQUIRED)
if (${BUILD_SWIG} EQUAL TRUE )
include(UseSWIG)
INCLUDE_DIRECTORIES(/usr/include/python3.6)
INCLUDE_DIRECTORIES(.src/Interface)
FIND_PACKAGE(PythonLibs)
SET(CMAKE_SWIG_FLAGS "-DSWIGWORDSIZE64")
SET(SWIG_OUTFILE_DIR "./")
SET(CMAKE_SWIG_OUTDIR ${CMAKE_BINARY_DIR}/slsv)

SET_SOURCE_FILES_PROPERTIES(./Interface.i PROPERTIES CPLUSPLUS ON)
SET_SOURCE_FILES_PROPERTIES(./Interface.i PROPERTIES SWIG_FLAGS "-includeall")
SWIG_ADD_LIBRARY(slsv_interface LANGUAGE python SOURCES ./Interface.i Interface.cpp V0.cpp ./Telnet/Telnet.cpp ./Telnet/libtelnet.cpp )
#SWIG_ADD_MODULE(slsv_interface python ./Interface.i Interface.cpp V0.cpp ./Telnet/Telnet.cpp ./Telnet/libtelnet.cpp )
#SWIG_ADD_LIBRARY(slsv_interface LANGUAGE python SOURCES ./Interface.i Interface.cpp V0.cpp V1.cpp V2.cpp V3.cpp V4.cpp)
#SWIG_ADD_MODULE(slsv_interface python ./Interface.i Interface.cpp V0.cpp V1.cpp V2.cpp V3.cpp V4.cpp)
SWIG_LINK_LIBRARIES(slsv_interface ${PYTHON_LIBRARIES})
endif(${BUILD_SWIG} EQUAL TRUE )


#add_library (Interface Interface.cpp V0.cpp V1.cpp V2.cpp V3.cpp V4.cpp)
add_library (Interface SHARED Interface.cpp V0.cpp ./Telnet/Telnet.cpp ./Telnet/libtelnet.cpp)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++11 ")
target_include_directories (Interface PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# TDD On V0 Interface
# add_executable(testIV0 V0.cpp Interface.cpp ./Telnet/Telnet.cpp ./Telnet/libtelnet.cpp ) // not really valid any more because of the external dependency

