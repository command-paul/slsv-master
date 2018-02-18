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
public:
	memoryMappedDevice(); //  Test constructor 
	memoryMappedDevice(uint start_address,uint end_address,bool R_RW = 0);
	memoryMappedDevice(uint start_address,uint lenght,bool R_RW = 0);
	~memoryMappedDevice();
	bool set_R_RW(uint start_address,uint end_address);
	bool set_R_RW(uint start_address,uint lenght);
	std::pair<bool,std::vector <int>> get_line(uint address,uint line_width);
	bool set_line(uint address,uint line_width,std::vector <int>);
	std::pair<bool,std::vector <int>> get_word(uint address);
	bool set_word(uint address,std::vector <int>);
private:
	uint base_address = 0;
	uint end_Address = 0;
	std::vector<uint_fast32_t> MEMORY;
	std::vector<bool> R_RW;
};

// class memory : public memoryMappedDevice {
// public:
// 	memory();
// 	~memory();
// //virtual std::vector <int> get_member(int address);
// private:
// int address0=;
// int word0 = 10;
// };

// class periphralA : public memoryMappedDevice {
// public:
// 	periphralA();
// 	~periphralA();
// private:
// int address0 = 2;
// int input0 = 20;
// };
