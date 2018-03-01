#include "Interface.hpp"

Interface::Interface(){
	return;
}

Interface::~Interface(){
	return;
}

bool Interface::Initialise(){
	return true;
}
// Syncronise
// Get it to the defined sync point
// Different policy for multi core
bool Interface::Synchronise(){
	return true;
}
// Update State
std::vector<std::pair<uint64_t,uint64_t>> Interface::Single_Step(){
	std::pair<uint64_t,uint64_t> pair_tst = std::make_pair(0,0);
	std::vector<std::pair<uint64_t,uint64_t>> memory;
	memory.push_back(pair_tst);
	return memory;
}
// return a vector of updates 
// Access HART & NHSV
std::pair<uint64_t,std::vector<uint32_t>> Interface::GetVariable(){
	std::vector<uint32_t> memory = std::vector<uint32_t>(10,0);
	std::pair<uint64_t,std::vector<uint32_t>> a = std::make_pair(true,memory);
	return a;
}
bool Interface::SetVariable(){
	return true;
}
// Access Memory
std::pair<uint64_t,std::vector<uint32_t>> Interface::GetMemory(){
	std::vector<uint32_t> memory = std::vector<uint32_t>(10,0);
	std::pair<uint64_t,std::vector<uint32_t>> a = std::make_pair(true,memory);
	return a;SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

FIND_PACKAGE(SWIG REQUIRED)
include(UseSWIG)
INCLUDE_DIRECTORIES(/usr/include/python3.5)
INCLUDE_DIRECTORIES(.src/Interface)
FIND_PACKAGE(PythonLibs)
SET(CMAKE_SWIG_FLAGS "-DSWIGWORDSIZE64")

SET_SOURCE_FILES_PROPERTIES(./Interface.i PROPERTIES CPLUSPLUS ON)
SET_SOURCE_FILES_PROPERTIES(./Interface.i PROPERTIES SWIG_FLAGS "-includeall")
SWIG_ADD_MODULE(slsv_interface python ./Interface.i Interface.cpp V0.cpp V1.cpp V2.cpp V3.cpp V4.cpp)
SWIG_LINK_LIBRARIES(slsv_interface ${PYTHON_LIBRARIES})

#execute_process(COMMAND python3 -c "from distutils.sysconfig import get_python_lib; print get_python_lib()" OUTPUT_VARIABLE PYTHON_SITE_PACKAGES OUTPUT_STRIP_TRAILING_WHITESPACE)
#install(TARGETS _slsv_state DESTINATION ${PYTHON_SITE_PACKAGES})
#install(FILES ${CMAKE_BINARY_DIR}/src/target.py DESTINATION ${PYTHON_SITE_PACKAGES})


add_library (Interface Telnet.cpp Interface.cpp V0.cpp V1.cpp V2.cpp V3.cpp V4.cpp)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++0x")
target_include_directories (Interface PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
}
bool Interface::SetMemory(){
	return true;
}
// Load Memory w/ Use Fastest method available to load the program memory 
std::pair<uint64_t,std::vector<uint32_t>> Interface::DumpMemory(){
	std::vector<uint32_t> memory = std::vector<uint32_t>(10,0);
	std::pair<uint64_t,std::vector<uint32_t>> a = std::make_pair(true,memory);
	return a;
}
bool Interface::LoadBinary(uint64_t address){
	return true;
}
// Checkpoint
// Record the entire accessable state from all reachable DUV`s
bool Interface::Checkpoint(std::string File){
	return true;
}
bool Interface::Checkpoint(){ // to the already defined checkpoint file :  /
	return true;
}
// Restore
bool Interface::Restore(std::string File){
	return true;
}
