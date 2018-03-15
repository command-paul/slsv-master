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
// // Update State
std::pair<std::vector<std::pair<uint32_t,uint64_t>>,std::vector<std::pair<uint64_t,uint64_t>>> Interface::Single_Step(){
	// FOR SLSV LEVEL 0 We will have to record everything and then return updates
	// updates based on weather there are any diferences from the current state
	// updates are comitted by test instance
	// This will need a reference to state :P TODO :: add ref to STATE
	
	// This Is getting cumbersome to type , TODO ::  TYPE DEF THESE STRUCTURES
	std::pair<uint32_t,uint64_t> Reg_update_frame = std::make_pair(0,0);
	std::pair<uint32_t,uint64_t> Mem_update_frame = std::make_pair(0,0);
	std::vector<std::pair<uint32_t,uint64_t>> Reg_update_vector;
	std::vector<std::pair<uint64_t,uint64_t>> Mem_update_vector; 
	// Single Step
	// This is a really big container that im moving around is there anything I can do to make this optimized for usage
	// of shared memory between threads ?
	std::pair<std::vector<std::pair<uint32_t,uint64_t>>,std::vector<std::pair<uint64_t,uint64_t>>> updates = std::make_pair(Reg_update_vector,Mem_update_vector);
	return updates;
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
	return a;
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
