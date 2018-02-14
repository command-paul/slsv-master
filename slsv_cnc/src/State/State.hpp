#include <vector>
// This class is a scalabale RISCV Architectural Unit
// Create Micro Architectural def in impl specific library / derive from shakti structures

class risc_v_HART;
class nonHARTStateVariables;
class memoryMappedDevice;
//class memory : memoryMappedDevice ;
//class periphralA : memoryMappedDevice;

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

private:
/*
Vector of HART`s
MemoryInterface
Non Hart State Registers
// Interrupts - How ??
// Debug Module Interface
*/
};

class risc_v_HART{
// A Riscv Architectural HART
// GPR
// FPR
// CSR
};

class nonHARTStateVariables{

};

class memoryMappedDevice{

};

class memory : memoryMappedDevice {

};

class periphralA : memoryMappedDevice {

};
