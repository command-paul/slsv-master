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

}

// CLASS :: risc_v_HART
// CLASS :: nonHARTStateVariables
// CLASS :: memoryMappedDevice
// CLASS :: memory
// CLASS :: periphralA


