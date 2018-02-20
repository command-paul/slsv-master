#include "Interface.hpp"
// This describes the interface to update the state container with a SLSV level 0 Setup;

// Method to just get state updates
// Method to step and then get updates


// initialisation to connect to an openOcd interface.
// something to see if the connection is still alive and well,
// Comms in binary format for commpactness
// Calls on other library to assist with the telnet implementation
// Calls methods over the selected adapter and does it business
    // Cut open ocd out of the picture ?
    // Use Open OCD as a library ?
    // extern to openocd target support in C


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
	// bool set_ocd_port(uint32_t port);
	// bool set_ocd_ip(char* ip);
};

V0::V0(){

}
// Destructor
V0::~V0(){

}
// Initialise 
bool V0::Initialise(){

}
// Syncronise
// Get it to the defined sync point
// Different policy for multi core
bool V0::Synchronise(){

}
// Update State
std::vector<std::pair<uint64_t,uint64_t>> V0::Single_Step(){

}
// return a vector of updates 
// Access HART & NHSV
std::pair<uint64_t,std::vector<uint32_t>> V0::GetVariable(){

}
bool V0::SetVariable(){

}
// Access Memory
std::pair<uint64_t,std::vector<uint32_t>> V0::GetMemory(){

}
bool V0::SetMemory(){

}
// Load Memory w/ Use Fastest method available to load the program memory 
std::pair<uint64_t,std::vector<uint32_t>> V0::DumpMemory(){

}
bool V0::LoadBinary(uint64_t address){

}
// Checkpoint
// Record the entire accessable state from all reachable DUV`s
bool V0::Checkpoint(std::string File){

}
bool V0::Checkpoint(){ // to the already defined checkpoint file :  /

}
// Restore
bool V0::Restore(std::string File){

}
