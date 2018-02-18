/* Interface file for State.cpp 
%include <std_string.i>
*/


%module slsv_state
%{
/* Header files or functon declaritions here */
	#include "State.hpp"
%}
%include "std_vector.i"
%include "typemaps.i"
%template(HartVector) std::vector <risc_v_HART> ;
%template(MemVector0) std::vector <memoryMappedDevice> ;
%template(IntVec) std::vector <int> ;
%template(NHSVVector) std::vector <nonHARTStateVariables> ;
class risc_v_HART;
class nonHARTStateVariables;
class memoryMappedDevice;


class riscv{
// A RISCV Architectural Core
public:
riscv();
~riscv();

std::vector <risc_v_HART> HART_Vec;
std::vector <memoryMappedDevice> Memory;
std::vector <nonHARTStateVariables> NHSV;

bool addHART();		//OverLoad
bool addMemory();	//OverLoad
bool addNHSV();		//OverLoad

/*
Vector of HART`s
MemoryInterface
Non Hart State Registers
// Interrupts - How ??
// Debug Module Interface
*/
};

class risc_v_HART{
public:
// A Riscv Architectural HART
int GPR = 1;
// GPR
// FPR
// CSR
};

class nonHARTStateVariables{
public:
int variable[7] = {0,1,2,3,4,5,6};
};

class memoryMappedDevice{
	memoryMappedDevice();
	virtual std::vector <int> get_member(int address);
private:
	int address0 = 0;
};

