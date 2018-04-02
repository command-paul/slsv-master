SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/SLSV)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

FIND_PACKAGE(SWIG REQUIRED)
include(UseSWIG)
INCLUDE_DIRECTORIES(/usr/include/python3.6)
INCLUDE_DIRECTORIES(.src/Interface)
FIND_PACKAGE(PythonLibs)
SET(CMAKE_SWIG_FLAGS "-DSWIGWORDSIZE64")
SET(SWIG_OUTFILE_DIR "./")
SET(CMAKE_SWIG_OUTDIR ${CMAKE_BINARY_DIR}/SLSV)

SET_SOURCE_FILES_PROPERTIES(./Interface.i PROPERTIES CPLUSPLUS ON)
SET_SOURCE_FILES_PROPERTIES(./Interface.i PROPERTIES SWIG_FLAGS "-includeall")
SWIG_ADD_LIBRARY(slsv_interface LANGUAGE python SOURCES ./Interface.i Interface.cpp V0.cpp ./Telnet/Telnet.cpp ./Telnet/libtelnet.cpp )
#SWIG_ADD_MODULE(slsv_interface python ./Interface.i Interface.cpp V0.cpp ./Telnet/Telnet.cpp ./Telnet/libtelnet.cpp )
#SWIG_ADD_LIBRARY(slsv_interface LANGUAGE python SOURCES ./Interface.i Interface.cpp V0.cpp V1.cpp V2.cpp V3.cpp V4.cpp)
#SWIG_ADD_MODULE(slsv_interface python ./Interface.i Interface.cpp V0.cpp V1.cpp V2.cpp V3.cpp V4.cpp)
SWIG_LINK_LIBRARIES(slsv_interface ${PYTHON_LIBRARIES})

#execute_process(COMMAND python3 -c "from distutils.sysconfig import get_python_lib; print get_python_lib()" OUTPUT_VARIABLE PYTHON_SITE_PACKAGES OUTPUT_STRIP_TRAILING_WHITESPACE)
#install(TARGETS _slsv_state DESTINATION ${PYTHON_SITE_PACKAGES})
#install(FILES ${CMAKE_BINARY_DIR}/src/target.py DESTINATION ${PYTHON_SITE_PACKAGES})


#add_library (Interface Interface.cpp V0.cpp V1.cpp V2.cpp V3.cpp V4.cpp)
add_library (Interface SHARED Interface.cpp V0.cpp)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
target_include_directories (Interface PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# TDD On V0 Interface
add_executable(testIV0 V0.cpp Interface.cpp ./Telnet/Telnet.cpp ./Telnet/libtelnet.cpp )
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++11 ")
