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
#ifndef Interface_V0_H
#define Interface_V0_H

#include "../../TestInstance.hpp"
#include "../Telnet/libtelnet.hpp"

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
	bool configureV0(std::string IP,std::string PORTS,uint32_t ABITS, uint32_t WIDTH);
private:
	std::string ip;
	std::string port;
	uint32_t abits;
	uint32_t width;
	TelnetOCD* Transport;
};

#endif