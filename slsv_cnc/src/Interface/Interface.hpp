#include <iostream>
#include <vector>
#include <cstdint>

#pragma once
// This is the Interface Header file for the SLSV CNC Server

/*
	This file essentially provides a bunnch of methods to the parent Device and test instance sets 
	the methds being provided as wrappers to the entire library of the access versions for V0 - V5
*/

// This provides the most crude access interface 
// Access policies will have to be defined inside each of the 
// Version files
class Interface{
public:
	// Constructors
	Interface();
	// Destructor
	virtual ~Interface();
	// Initialise 
	virtual bool Initialise();
	// Syncronise
	// Get it to the defined sync point
	// Different policy for multi core
	virtual bool Synchronise();
	// Update State
	virtual std::vector<std::pair<uint64_t,uint64_t>> Single_Step();
	// return a vector of updates 
	// Access HART & NHSV
	virtual std::pair<uint64_t,std::vector<uint32_t>> GetVariable();
	virtual bool SetVariable();
	// Access Memory
	virtual std::pair<uint64_t,std::vector<uint32_t>> GetMemory();
	virtual bool SetMemory();
	// Load Memory w/ Use Fastest method available to load the program memory 
	virtual std::pair<uint64_t,std::vector<uint32_t>> DumpMemory();
	virtual bool LoadBinary(uint64_t address);
	// Checkpoint
	// Record the entire accessable state from all reachable DUV`s
	virtual bool Checkpoint(std::string File);
	virtual bool Checkpoint(); // to the already defined checkpoint file :/
	// Restore
	virtual bool Restore(std::string File);
	// Restore the checkpoint state to the core and set/reset state variables as defined by user.
	// Utility Methods -- Should be defined in derived interface classes
	// bool set_ocd_port(uint32_t port);
	// bool set_ocd_ip(char* ip);
private:
	//this is the Function Vector;
	std::string CheckpointFile;
	bool initialised = 0;
};

