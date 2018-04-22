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
#ifndef Test_Instance_h
#define Test_Instance_h

#include "Interface/Interface.hpp"
//#include "Interface/V0.hpp" // Rework this to something better  Is this Necessery since ive included the parent class ?
#include "Coverage/Coverage.hpp"
#include "State/State.hpp"
#include "events.hpp"
#include <vector>
#include "Commons.hpp"

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
    bool run();// Design a better run control system and implement
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
    uint eventID;
    bool initialise();
    bool testInterfaces();
    bool testRegisters();
    bool testMemory();
    bool run();// Design a better run control system and implement
    bool checkpoint();
    bool restore();
    std::vector<Coverage*> coverageTrackers;
    bool addCoverageTracker();
};

#endif