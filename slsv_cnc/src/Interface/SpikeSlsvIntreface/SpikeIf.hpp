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
#ifndef Spike_LowOH_Interface
#define Spike_LowOH_Interface

// SLSV Libraries
#include "../../TestInstance.hpp" // SLSV Interface Template // Interface.hpp has been add to the same folder for code simplicity 
#include <iostream>
#include <vector>
#include <string>

// Spike Libraries 
#include "sim.h"
#include "mmu.h"
#include "remote_bitbang.h"
#include "cachesim.h"
#include "extension.h"
#include <dlfcn.h>
#include <fesvr/option_parser.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <memory>

// Include File to get directly innto spike
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
	// Access HART & NHSV :: Address
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


/*

static void help()
{
  fprintf(stderr, "usage: spike [host options] <target program> [target options]\n");
  fprintf(stderr, "Host Options:\n");
  fprintf(stderr, "  -p<n>                 Simulate <n> processors [default 1]\n");
  fprintf(stderr, "  -m<n>                 Provide <n> MiB of target memory [default 2048]\n");
  fprintf(stderr, "  -m<a:m,b:n,...>       Provide memory regions of size m and n bytes\n");
  fprintf(stderr, "                          at base addresses a and b (with 4 KiB alignment)\n");
  fprintf(stderr, "  -d                    Interactive debug mode\n");
  fprintf(stderr, "  -g                    Track histogram of PCs\n");
  fprintf(stderr, "  -l                    Generate a log of execution\n");
  fprintf(stderr, "  -h                    Print this help message\n");
  fprintf(stderr, "  -H                    Start halted, allowing a debugger to connect\n");
  fprintf(stderr, "  --isa=<name>          RISC-V ISA string [default %s]\n", DEFAULT_ISA);
  fprintf(stderr, "  --pc=<address>        Override ELF entry point\n");
  fprintf(stderr, "  --hartids=<a,b,...>   Explicitly specify hartids, default is 0,1,...\n");
  fprintf(stderr, "  --ic=<S>:<W>:<B>      Instantiate a cache model with S sets,\n");
  fprintf(stderr, "  --dc=<S>:<W>:<B>        W ways, and B-byte blocks (with S and\n");
  fprintf(stderr, "  --l2=<S>:<W>:<B>        B both powers of 2).\n");
  fprintf(stderr, "  --extension=<name>    Specify RoCC Extension\n");
  fprintf(stderr, "  --extlib=<name>       Shared library to load\n");
  fprintf(stderr, "  --rbb-port=<port>     Listen on <port> for remote bitbang connection\n");
  fprintf(stderr, "  --dump-dts            Print device tree string and exit\n");
  fprintf(stderr, "  --progsize=<words>    progsize for the debug module [default 2]\n");
  fprintf(stderr, "  --debug-sba=<bits>    debug bus master supports up to "
      "<bits> wide accesses [default 0]\n");
  exit(1);
}
*/

#endif