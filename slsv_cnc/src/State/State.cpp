// This is a scalable container for any RISC-V Compliant SOC
// Compliant as far as February 2018 State of published Specs
#define DEBUG 1
#define VERBOSITY 3
//#define VERBOSITY 2
//#define VERBOSITY 1
//#define VERBOSITY 0
#ifdef DEBUG	// Libraries for Debug 
	#include <iostream>
#endif
#include <vector>
#include "State.hpp"
// CLASS :: riscv
riscv::riscv(){
	#if DEBUG != 0  && VERBOSITY == 3// Debug Needs to be better
		std::cout << "Hello Riscv !" << std::endl;
	#endif
}
riscv::~riscv(){
	#if DEBUG != 0  && VERBOSITY == 3// Debug Needs to be better
		std::cout << "Bye Riscv !" << std::endl;
	#endif	
}

bool riscv:: addHART(){
	risc_v_HART NewHart = risc_v_HART((uint32_t)HART_Vec.size());
	if(&NewHart == NULL) return 0;
	#if DEBUG != 0  && VERBOSITY == 3// Debug Needs to be better
		std::cout << "New HART Created" << std::endl;
	#endif	
	HART_Vec.push_back(NewHart); 
	return true;
}


bool riscv:: addMemory(){
	memoryMappedDevice NewMemory = memoryMappedDevice(0,false,100);
	if(&NewMemory == NULL) return 0;
	#if DEBUG != 0  && VERBOSITY == 3// Debug Needs to be better
		std::cout << "New Memory Created" << std::endl;
	#endif	
	Memory.push_back(NewMemory); 
	return true;
}
// std::vector <int> memoryMappedDevice::get_member(int address){
	
// 	a.push_back(1);
// 	return a;
// }
bool riscv::addNHSV(){
	nonHARTStateVariables NewNHSV = nonHARTStateVariables();
	if(&NewNHSV == NULL) return 0;
	#if DEBUG != 0  && VERBOSITY == 3// Debug Needs to be better
		std::cout << "New NHSV Created" << std::endl;
	#endif	
	NHSV.push_back(NewNHSV); 
	return true;
}
bool riscv::memoryChainValid(){
	return true;
}
bool riscv::NHSVChainValid(){
	return true;
}

// CLASS :: risc_v_HART
risc_v_HART::risc_v_HART(){
	return;
}
risc_v_HART::risc_v_HART(uint32_t HARTID){
	hart_id = HARTID;
	return;
}
risc_v_HART::~risc_v_HART(){
	return;
}
// CLASS :: nonHARTStateVariables
bool nonHARTStateVariables::set_R_RW(uint32_t startID,uint32_t endID){
	base_ID = startID;
	end_ID = endID;
	regFile = std::vector<uint_fast64_t>(end_ID-base_ID,0);
	R_RW = std::vector<bool>(end_ID-base_ID,0);
	//work out validity constrints
	return true;
}
bool nonHARTStateVariables::set_R_RW_L(uint32_t startID,uint32_t elements){
	return true;
}
std::pair<bool,std::vector <uint32_t>> nonHARTStateVariables::get_line(uint32_t reg_ID,uint32_t line_width){
	std::pair<bool,std::vector <uint32_t>> a;
	std::vector <uint32_t> Tvect = std::vector <uint32_t>(1,1);
	a = std::make_pair(true,Tvect);
	return a;
}
bool nonHARTStateVariables::set_line(uint64_t regID,uint64_t line_width,std::vector <uint32_t>){
	return true;
}
std::pair<bool,std::vector <uint32_t>> nonHARTStateVariables::get_word(uint64_t regID){
	std::pair<bool,std::vector <uint32_t>> a;
	std::vector <uint32_t> Tvect = std::vector <uint32_t>(1,1);
	a = std::make_pair(true,Tvect);
	return a;
}
bool nonHARTStateVariables::set_word(uint64_t regID,std::vector <uint32_t>){
	return true;
}
// CLASS :: memoryMappedDevice

// TEST_Constructor
memoryMappedDevice::memoryMappedDevice(){
	return;
}
// Destructor
memoryMappedDevice::~memoryMappedDevice(){
	return;
}
// Start End constructor
memoryMappedDevice::memoryMappedDevice(uint64_t start_address,uint64_t end_address,bool RRW){
	return;
}
// Start Len Constructor
memoryMappedDevice::memoryMappedDevice(uint64_t start_address,bool RRW ,uint64_t length){
	MEMORY.resize(length,0);
	R_RW.resize(length,RRW);
	base_address = start_address;
	end_address = base_address+length;
	return;	
}

bool memoryMappedDevice::set_R_RW(uint64_t start_address,uint64_t end_address){
	return true;
}

bool memoryMappedDevice::set_R_RW_L(uint64_t start_address,uint64_t length){
	return true;
}
std::pair<bool,std::vector <uint32_t>> memoryMappedDevice::get_line(uint64_t address,uint64_t line_width){
	std::pair<bool,std::vector <uint32_t>> a;
	std::vector<uint32_t> Tvect = std::vector<uint32_t>(MEMORY.begin()+address,MEMORY.begin()+address+line_width);
	a = std::make_pair(true,Tvect);
	return a;
}
bool memoryMappedDevice::set_line(uint64_t address,uint64_t line_width,std::vector <uint32_t>){
	return true;
}
std::pair<bool,std::vector <uint32_t>> memoryMappedDevice::get_word(uint64_t address){
	std::pair<bool,std::vector <uint32_t>> a;
	std::vector <uint32_t> Tvect = std::vector <uint32_t>(1,1);
	a = std::make_pair(true,Tvect);
	return a;
}
bool memoryMappedDevice::set_word(uint64_t address,std::vector <uint32_t>){
	return true;
}
