
#FIND_PACKAGE(SWIG REQUIRED)
#INCLUDE(./src/swig_cmake_test.i)
#include(UseSWIG)
#INCLUDE_DIRECTORIES(/usr/include/python3.5)
#project(swig_cmake_test)
#FIND_PACKAGE(PythonLibs)
#SET(CMAKE_SWIG_FLAGS "")
#SET_SOURCE_FILES_PROPERTIES(./src/swig_cmake_test.i PROPERTIES CPLUSPLUS ON)
#SET_SOURCE_FILES_PROPERTIES(./src/swig_cmake_test.i PROPERTIES SWIG_FLAGS "-includeall")
#SWIG_ADD_MODULE(swig_cmake_test python ./src/swig_cmake_test.i ./src/swig_cmake_test.cpp)
#SWIG_LINK_LIBRARIES(swig_cmake_test ${PYTHON_LIBRARIES})
#add_executable(swig_cmake_test ./src/swig_cmake_test.cpp)


cmake_minimum_required(VERSION 2.6)

project(SLSV)
add_subdirectory(src/State)

add_executable(build ./src/TestInstance.cpp)

target_link_libraries (build LINK_PUBLIC State)