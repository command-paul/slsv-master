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
