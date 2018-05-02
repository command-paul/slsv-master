%module slsv_state
%{
/* Header files or functon declaritions here */
	#include "State.hpp"
%}

%define SWIGWORDSIZE64
%enddef

%include "stdint.i"
%include "std_vector.i"
%include "std_pair.i"
%include "typemaps.i"

%template(StateReg) std::vector<uint_fast64_t>;
%template(Tester1) std::vector <uint32_t>;
%template(TestRet) std::pair<bool,std::vector <uint32_t>>;
%template(HartVector) std::vector <risc_v_HART> ;
%template(MemVector0) std::vector <memoryMappedDevice> ;
%template(IntVec) std::vector <int> ;
%template(NHSVVector) std::vector <nonHARTStateVariables> ;


// Forward declaritions

class risc_v_HART;
class nonHARTStateVariables;
class memoryMappedDevice;
typedef  std::pair<INTLEN,INTLEN> update_t;
typedef  std::vector<update_t> UpdateFrame_t;
typedef  std::pair<UpdateFrame_t,UpdateFrame_t> traceFrame_t;


class riscv{ // rename this to riscv_State
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
	bool memoryChainValid();
	bool NHSVChainValid();
	uint32_t TopRegAddress = 65; // just GPR PC FPR right now 
	uint64_t get_register(uint32_t address); // This address is according to the State variable addressing scheme
	uint32_t updateTraceFrame(traceFrame_t frame);
	// HART Micro Architctural state variables need to be traced somehow the NHSV it masks the HART ID Fiels addressing scheme doesnt cover the smae
	std::pair<std::pair<uint64_t,uint64_t>,std::vector<uint_fast32_t>> MemoryMap; //Pair::((Pair::Start,End),Pointer);
	std::pair<std::pair<uint32_t,uint32_t>,std::vector<uint_fast32_t>> NHSVMap; //Pair::((Pair::Start,End),Pointer);
};

class risc_v_HART{
public:
	risc_v_HART();
	risc_v_HART(uint32_t HARTID);
	~risc_v_HART();
// A Riscv Architectural HART
	std::vector<uint_fast64_t> GPR = std::vector<uint_fast64_t>(32,0);
	std::vector<uint_fast64_t> FPR = std::vector<uint_fast64_t>(32,0);
	std::vector<uint_fast64_t> CSR = std::vector<uint_fast64_t>(4096,0);
	uint_fast64_t PC;
	uint32_t hart_id;
};

class nonHARTStateVariables{
public:
	bool set_R_RW(uint32_t startID,uint32_t endID);
	bool set_R_RW_L(uint32_t startID,uint32_t elements);
	std::pair<bool,std::vector <uint32_t>> get_line(uint32_t reg_ID,uint32_t line_width);
	bool set_line(uint64_t regID,uint64_t line_width,std::vector <uint32_t>);
	std::pair<bool,std::vector <uint32_t>> get_word(uint64_t regID);
	bool set_word(uint64_t regID,std::vector <uint32_t>);
	uint64_t base_ID = 0;
	uint64_t end_ID = 0;
	std::vector<uint_fast64_t> regFile;
	std::vector<bool> R_RW;
}; // NHSV is deprecated because its in effective for uarch state variables ::
// This loks lie a good solution for tracking implementation specific architectural hidden variables

class memoryMappedDevice{
public:
	memoryMappedDevice(); //  Test constructor 
	memoryMappedDevice(uint64_t start_address,uint64_t end_address,bool RRW = 0);
	memoryMappedDevice(uint64_t start_address,bool RRW ,uint64_t length);
	~memoryMappedDevice();
	bool set_R_RW(uint64_t start_address,uint64_t end_address);
	bool set_R_RW_L(uint64_t start_address,uint64_t length);
	std::pair<bool,std::vector <uint32_t>> get_line(uint64_t address,uint64_t line_width);
	bool set_line(uint64_t address,uint64_t line_width,std::vector <uint32_t>);
	std::pair<bool,std::vector <uint32_t>> get_word(uint64_t address);
	bool set_word(uint64_t address,std::vector <uint32_t>);
	uint32_t position;
	uint64_t base_address = 0;
	uint64_t end_address = 0;
	std::vector<uint_fast32_t> MEMORY;
	std::vector<bool> R_RW;
};