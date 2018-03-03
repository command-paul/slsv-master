#include "Interface.hpp"
#include "../State/State.hpp"
#include "./Telnet/libtelnet.hpp"

class V0 : private Interface{
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
	std::vector<std::pair<uint64_t,uint64_t>> Single_Step()  override;
	// return a vector of updates 
	// Access HART & NHSV
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
};
