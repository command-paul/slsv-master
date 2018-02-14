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

std::vector <risc_v_HART*> HART_Vec;
std::vector <memoryMappedDevice*> Memory;
std::vector <nonHARTStateVariables*> NHSV;

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
int variable = 0;
};

class memoryMappedDevice{
public:
int address0 = 0;
};

class memory : public memoryMappedDevice {
public:
int address0=1;
int word0 = 10;
};

class periphralA : public memoryMappedDevice {
public:
int address0 = 2;
int input0 = 20;
};
