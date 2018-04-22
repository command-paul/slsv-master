/*-------------------------------------------------------------------------------------------------- 
* Copyright (c) 2018, IIT Madras All rights reserved.
* 
* Redistribution and use in source and binary forms, with or without modification, are permitted
* provided that the following conditions are met:
* 
* - Redistributions of source code must retain the below copyright notice, this list of conditions
*   and the following disclaimer.  
* - Redistributions in binary form must reproduce the above copyright notice, this list of 
*   conditions and the following disclaimer in the documentation and/or other materials provided 
*   with the distribution.  
* - Neither the name of IIT Madras  nor the names of its contributors may be used to endorse or 
*   promote products derived from this software without specific prior written permission.
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
* AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
* IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
* OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* --------------------------------------------------------------------------------------------------
* Author:  Paul George
* Email id: pg456@snu.edu.in
* ------------------------------------------------------------------------------------------------*/
#ifndef Interface_H
#define Interface_H

#include <iostream>
#include "../Commons.hpp"
#include "../State/State.hpp"
#include "../Coverage/Coverage.hpp"
#include "../events.hpp"
#include "../TestInstance.hpp"

 // Forward declarition Will find out if this works or not :/
class Device;

// This is the Interface Header file for the SLSV CNC Servcleaer

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
	virtual bool Initialise() = 0;
	// Syncronise
	// Get it to the defined sync point
	// Different policy for multi core
	virtual bool Synchronise() = 0;
	// Update State
	virtual bool Single_Step() = 0;
	// return a vector of updates pair of Registers and memory
	// Access HART & NHSV
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

// typedef std::pair<uint32_t,uint64_t> p1;
// typedef std::pair<uint64_t,uint64_t> p2;
// typedef std::vector<p1> RegUpdate;
// typedef std::vector<p2> MemUpdate;
// typedef std::pair<RegUpdate,MemUpdate> StateContainer;

#endif