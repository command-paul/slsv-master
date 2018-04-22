%module slsv_interface
%{
/* Header files or functon declaritions here */
	//#include "../src/Interface/Interface.hpp"
	//#include "../src/Interface/V0.hpp"
	//#import "../src/Interface/Telnet/libtelnet.hpp"
	#include "Interface.hpp"
	#include "V0.hpp"
	#import "Telnet/libtelnet.hpp"
%}

%define SWIGWORDSIZE64
%enddef
%include "stdint.i"
%include "std_vector.i"
%include "std_pair.i"
%include "typemaps.i"
%include "std_string.i"


//%template(regUpdateFrame) std::vector<std::pair<INTLEN,INTLEN>>;
//%template(memUpdateFrame) std::vector<std::pair<INTLEN,INTLEN>>;
//%template(traceFrame) std::pair<regUpdateFrame,memUpdateFrame>;


// %template(lop1) std::pair<uint32_t,uint64_t>;
// %template(lop2) std::pair<uint64_t,uint64_t>;
// //%template(single_step_v1) std::vector<std::pair<uint64_t,uint64_t>>;
// //%template(single_step_v2) std::vector<std::pair<uint32_t,uint64_t>>;
// //%template(single_step) std::pair<single_step_v1,single_step_v2> ;
// %template(single_step_ctr) std::pair<std::vector<std::pair<uint32_t,uint64_t>>,std::vector<std::pair<uint64_t,uint64_t>>>;

// Interface - pure virtual
class Interface{
public:
	// Constructors
	Interface();
	// Destructor
	virtual ~Interface();
	// Initialise 
	virtual bool Initialise() = 0;
	// Syncronise
	// Get it to the defined sync point
	// Different policy for multi core
	virtual bool Synchronise() = 0;
	// Update State
	virtual traceFrame Single_Step() = 0;
	// return a vector of updates pair of Registers and memory
	virtual std::pair<uint64_t,std::vector<uint32_t>> GetVariable() = 0;
	virtual bool SetVariable() = 0;
	// Access Memory
	virtual std::pair<uint64_t,std::vector<uint32_t>> GetMemory() = 0;
	virtual bool SetMemory() = 0;
	// Load Memory w/ Use Fastest method available to load the program memory 
	virtual std::pair<uint64_t,std::vector<uint32_t>> DumpMemory() = 0;
	virtual bool LoadBinary(uint64_t address) = 0;
	// Checkpoint
	// Record the entire accessable state from all reachable DUV`s
	virtual bool Checkpoint(std::string File) = 0;
	virtual bool Checkpoint() = 0; 
	// Restore
	virtual bool Restore(std::string File) = 0;
	// Restore the checkpoint state to the core and set/reset state variables as defined by user.
	// Utility Methods -- Should be defined in derived interface classes
	// bool set_ocd_port(uint32_t port);
	// bool set_ocd_ip(char* ip);
private:
	//this is the Function Vector;
	std::string CheckpointFile;
	bool initialised = 0;
};

class V0 : public Interface{
public:
    // Constructors
    V0();
	// Destructor
    ~V0() override ;
	// Initialise 
	bool Initialise()  override;
	// Syncronise
	// Get it to the defined sync point
	// Different policy for multi core
	bool Synchronise()  override;
	// Update State
	traceFrame Single_Step()  override;
	// return a vector of updates 
	// Access HART + NHSV
	std::pair<uint64_t,std::vector<uint32_t>> GetVariable()  override;
	bool SetVariable()  override;
	// Access Memory
	std::pair<uint64_t,std::vector<uint32_t>> GetMemory()  override;
	bool SetMemory()  override;
	// Load Memory w/ Use Fastest method available to load the program memory 
	std::pair<uint64_t,std::vector<uint32_t>> DumpMemory()  override;
	bool LoadBinary(uint64_t address)  override;
	// Checkpoint
	// Record the entire accessable state from all reachable DUV`s
	bool Checkpoint(std::string File)  override;
	bool Checkpoint() override; // to the already defined checkpoint file :  /
	// Restore
	bool Restore(std::string File)  override;
	// Restore the checkpoint state to the core and set/reset state variables as defined by user.
	// Utility Methods -- Should be defined in derived interface classes
	//bool set_ocd_port(uint32_t port);
	//bool set_ocd_ip(char* ip);
	bool configureV0(std::string IP,std::string PORTS,uint32_t ABITS, uint32_t WIDTH);

private:
	std::string ip;
	std::string port;
	uint32_t abits;
	uint32_t width;
	TelnetOCD* Transport;
};
