#include "V0.hpp"
// This describes the interface to update the state container with a SLSV level 0 Setup;

// Method to just get state updates
// Method to step and then get updates


// initialisation to connect to an openOcd interface.
// something to see if the connection is still alive and well,
// Comms in binary format for commpactness
// Calls on other library to assist with the telnet implementation
// Calls methods over the selected adapter and does it business
    // Cut open ocd out of the picture ?
    // Use Open OCD as a library ?
    // extern to openocd target support in C

V0::V0(){
	return;
}
// Destructor
V0::~V0(){
	return;
}
// Initialise 
bool V0::Initialise(){
	return true;
}
// Syncronise
// Get it to the defined sync point
// Different policy for multi core
bool V0::Synchronise(){
	return true;
}
// Update State
std::vector<std::pair<uint64_t,uint64_t>> V0::Single_Step(){
	std::pair<uint64_t,uint64_t> pair_tst = std::make_pair(0,0);
	std::vector<std::pair<uint64_t,uint64_t>> memory;
	memory.push_back(pair_tst);
	return memory;
}
// return a vector of updates 
// Access HART & NHSV
std::pair<uint64_t,std::vector<uint32_t>> V0::GetVariable(){
	std::vector<uint32_t> memory = std::vector<uint32_t>(10,0);
	std::pair<uint64_t,std::vector<uint32_t>> a = std::make_pair(true,memory);
	return a;
}
bool V0::SetVariable(){
	return true;
}
// Access Memory
std::pair<uint64_t,std::vector<uint32_t>> V0::GetMemory(){
	std::vector<uint32_t> memory = std::vector<uint32_t>(10,0);
	std::pair<uint64_t,std::vector<uint32_t>> a = std::make_pair(true,memory);
	return a;
}
bool V0::SetMemory(){
	return true;
}
// Load Memory w/ Use Fastest method available to load the program memory 
std::pair<uint64_t,std::vector<uint32_t>> V0::DumpMemory(){
	std::vector<uint32_t> memory = std::vector<uint32_t>(10,0);
	std::pair<uint64_t,std::vector<uint32_t>> a = std::make_pair(true,memory);
	return a;
}
bool V0::LoadBinary(uint64_t address){
	return true;
}
// Checkpoint
// Record the entire accessable state from all reachable DUV`s
bool V0::Checkpoint(std::string File){
	return true;
}
bool V0::Checkpoint(){ // to the already defined checkpoint file :  /
	return true;
}
// Restore
bool V0::Restore(std::string File){
	return true;
}

bool V0::set_ocd_port(uint32_t port){
	return true;
}
bool V0::set_ocd_ip(char* ip){
	return true;
}
