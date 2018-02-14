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
	risc_v_HART* NewHart = new risc_v_HART;
	if(NewHart == NULL) return 0;
	#if DEBUG != 0  && VERBOSITY == 3// Debug Needs to be better
		std::cout << "New HART Created" << std::endl;
	#endif	
	HART_Vec.push_back(NewHart); 
	return true;
}


bool riscv:: addMemory(){
	memoryMappedDevice* NewMemory = new memoryMappedDevice;
	memoryMappedDevice* NewMemoryA = new memory;
	memoryMappedDevice* NewMemoryB = new periphralA;
	if(NewMemory == NULL) return 0;
	if(NewMemoryA == NULL) return 0;
	if(NewMemoryB == NULL) return 0;
	#if DEBUG != 0  && VERBOSITY == 3// Debug Needs to be better
		std::cout << "New Memory Created" << std::endl;
	#endif	
	Memory.push_back(NewMemory); 
	Memory.push_back(NewMemoryA); 
	Memory.push_back(NewMemoryB); 
	return true;
}


bool riscv:: addNHSV(){
	nonHARTStateVariables* NewNHSV = new nonHARTStateVariables;
	if(NewNHSV == NULL) return 0;
	#if DEBUG != 0  && VERBOSITY == 3// Debug Needs to be better
		std::cout << "New NHSV Created" << std::endl;
	#endif	
	NHSV.push_back(NewNHSV); 
	return true;
}
// CLASS :: risc_v_HART
// CLASS :: nonHARTStateVariables
// CLASS :: memoryMappedDevice
// CLASS :: memory
// CLASS :: periphralA


