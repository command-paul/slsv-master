%module slsv_interface
%{
/* Header files or functon declaritions here */
	//#include "../TestInstance.hpp"
	#include "Interface.hpp"
	#include "V0/V0.hpp"
	#include "SpikeSlsvIntreface/SpikeIf.hpp"
%}

%include "stdint.i"
%include "std_vector.i"
%include "std_pair.i"
%include "typemaps.i"
%include "std_string.i"

class Device;

%factory(Interface ,V0 ,SpikeIf );

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
	virtual uint32_t Single_Step() = 0;
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
	virtual bool Checkpoint() = 0; // to the already defined checkpoint file :/
	// Restore
	virtual bool Restore(std::string File) = 0;
	// Restore the checkpoint state to the core and set/reset state variables as defined by user.
	// Utility Methods -- Should be defined in derived interface classes
	// bool set_ocd_port(uint32_t port);
	// bool set_ocd_ip(char* ip);
	Device* Parent;
private:
	//this is the Function Vector;
	std::string CheckpointFile;
	bool initialised = 0;
};



class V0 : public Interface{
public:
    // Constructors
    V0();
	V0(Device* parentPointer);
	// Destructor
    ~V0() override ;
	// Initialise 
	bool Initialise()  override;
	// Syncronise
	// Get it to the defined sync point
	// Different policy for multi core
	bool Synchronise()  override;
	// Update State
	uint32_t Single_Step()  override;
	// return a vector of updates 
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
	bool set_ocd_port(uint32_t port);
	bool set_ocd_ip(char* ip);
	bool configureV0(std::string IP,std::string PORTS,uint32_t ABITS, uint32_t WIDTH);
private:
	std::string ip;
	std::string port;
	uint32_t abits;
	uint32_t width;
	TelnetOCD* Transport;
};


class SpikeIf : public Interface{
public:
    // Constructors
    SpikeIf();
	// Destructor
    ~SpikeIf() override ;
	bool destroy_s();
	//Spike Command Line Arguments 
	bool setISA(std::string);
	bool setProcessors(u_int16_t);
	bool setMiB(u_int16_t);
	bool setMVect(std::vector<std::pair<uint64_t,u_int64_t>>);
	bool setPC(uint64_t);
	bool setPK();
	bool setElfToLoad();
	bool setHalted(bool Halted);
	bool genSpikeArguments();
	// Other NFU Options can be implemented later. reference left below for spike as of Apr 9 2018

	// Initialise essentially passes the configuration argument and starts and waits for a command
	bool Initialise()  override;
	
	// Syncronise
	// Get it to the defined sync point which is the Ebreak at start address.
	// Different policy for multi core
	bool Synchronise()  override;

	// Single_Step // Get all the updates that happened over the course of a single step
	uint32_t Single_Step()  override;
	
	// return a vector of updates 
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

	sim_t* s;
	std::string SpikeArguments = "/home/commandpaul/slsv-master/test_vectors/Tests/test0.rv64imafd";
	// donot Leave any superfluous spaces
};
