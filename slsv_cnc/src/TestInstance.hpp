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

* ------------------------------------------------------------------------------------------------*/
#ifndef Test_Instance_h
#define Test_Instance_h

#include "Interface/Interface.hpp"
#include "Coverage/Coverage.hpp"
#include "State/State.hpp"
#include "events.hpp"
#include <vector>
#include "Commons.hpp"


typedef  std::pair<INTLEN,INTLEN> update_t;
typedef  std::vector<update_t> UpdateFrame_t;
typedef  std::pair<UpdateFrame_t,UpdateFrame_t> traceFrame_t;


class Interface; // Some Circular dep issue only sitting with interface so far ;
class Coverage;
class traceCache;

// #define XLEN 64

// #if XLEN == 64
//     #define INTLEN uint64_t
// #else if XLEN == 32 
//     #define INTLEN uint32_t
// #endif

// // TraceFrames
// typedef  std::vector<std::pair<INTLEN,INTLEN>> regUpdateFrame;
// typedef  std::vector<std::pair<INTLEN,INTLEN>> memUpdateFrame;
// typedef  std::pair<regUpdateFrame,memUpdateFrame> traceFrame;

// This code is starting to get ugly now because of sphegatti references of forward decls and inncludes.

// Dear Reader SWIG does not support CPP17 touples as of Feb/March now so the code is a messy
// Mix of Vector and pair Containers , I hope future maintainance leverages this to make
// SLSV more interactable . Note This would be Scripting laguage specific therefore will have to be done in phases

// Device Class abstracting State containers and interfaces.
class Device{
public:	
	Device();
	~Device();
	riscv* DUV;
	Interface* Bridge;
	// Somehow make a little vector of all the listed coverage metrics
	std::string deviceName;
	// Trace Cache of uncomitted state updates pair (vector pair)
    traceCache* Cache;
};

// LockStep Verification Test Setup    
class LockStep_Verification{
public:
    Device deviceA;
    Device deviceB;
    bool eventPending;
    uint eventID;

    bool initialise();
    bool loadTestVector();
    uint32_t run();// Design a better run control system and implement
    bool checkpoint();
    bool restore();

    std::vector<Coverage*> coverageTrackers;
    bool addCoverageTracker();
};

// Other Classes describing other Verification setup Configurations
class basicDeviceTests{
public:
    Device DUT;
    bool eventPending;
    uint32_t eventID;
    bool initialise();
    bool testInterfaces();
    bool testRegisters();
    bool testMemory();
    uint32_t run();// Design a better run control system and implement
    bool checkpoint();
    bool restore();
    std::vector<Coverage*> coverageTrackers;
    bool addCoverageTracker();
};

// Should I integrate the trace cache intot he coverage module section  ?? Me thinks yes .
class traceCache{
public:
    riscv* ScratchState; 
	// The above is my sacraficeing space for commputational overhead & time to functional deployment
	Device* Parent;
    traceCache();
	//traceCache(uint32_t max_len);    // ease of use - later not in testing :P
    ~traceCache();

    std::vector<traceFrame_t> Cache; 
    uint32_t max_length;
    uint32_t curr_length;
    std::vector<uint64_t> traceCommitMask ; // This restricts the Number of possible coverage trackers to 64
	uint64_t traceCommitClearMask = 0;
	// 1D Assert Clear
	// Trace Analysis Clear
	// Toggle Coverage Clear
	// 2D Assert Clear - can be disabled by Trace Analysis clear.
	// Alternatively for lockstep if PC not match pc Step the Device that matches a sequence 
    //bool configureScratchState();
    uint32_t enqueueTF(traceFrame_t frame);
    //bool commitTopFrame();
    //bool commitNFrames(uint32_t N);
	uint32_t updateScratch();
	uint32_t commitScratch();
};

#endif