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
#ifndef Coverage_H
#define Coverage_H

#define SVA_INDEX 4 // Total Number of defined assertion types  

#include <vector>
#include <cstdint>
#include <string>
#include "../events.hpp"
// #include "../State/State.hpp"
// #include "../Interface/Interface.hpp"
#include "../TestInstance.hpp"

class riscv;
class Assertion;
class Device; // Forward declarition
//Coverage event + Operational exception .

// Coverage can be associated with one or more than one device.
// The trace cache simply holds everything and allows for access clearing and raises an operational exception


//This is a base class of wrapper functions this defines tha basic interface behind which the different coverafe schemes operate.
// #include "../State/State.hpp"
#define XLEN 64

#if XLEN == 64
    #define INTLEN uint64_t
#else if XLEN == 32 
    #define INTLEN uint32_t
#endif

// TraceFrames
typedef  std::pair<INTLEN,INTLEN> update_t;
typedef  std::vector<update_t> UpdateFrame_t;
typedef  std::pair<UpdateFrame_t,UpdateFrame_t> traceFrame_t;

// Should I integrate the trace cache intot he coverage module section  ?? Me thinks yes .
// class traceCache{
// public:
//     riscv* ScratchState; 
// 	// The above is my sacraficeing space for commputational overhead & time to functional deployment
// 	Device* Parent;
//     traceCache();
// 	//traceCache(uint32_t max_len);    // ease of use - later not in testing :P
//     ~traceCache();

//     std::vector<traceFrame_t> Cache; 
//     uint32_t max_length;
//     uint32_t curr_length;
//     std::vector<uint64_t> traceCommitMask ; // This restricts the Number of possible coverage trackers to 64
// 	uint64_t traceCommitClearMask = 0;
// 	// 1D Assert Clear
// 	// Trace Analysis Clear
// 	// Toggle Coverage Clear
// 	// 2D Assert Clear - can be disabled by Trace Analysis clear.
// 	// Alternatively for lockstep if PC not match pc Step the Device that matches a sequence 
//     bool configureScratchState();
//     uint32_t enqueueTF(traceFrame_t frame);
//     bool commitTopFrame();
//     bool commitNFrames(uint32_t N);
// 	uint32_t updateScratch();
// 	uint32_t commitScratch();
// };

// my memory footprint is huge, I tbh can at each step compute the net effective state 
    
class Coverage{
public:
	Coverage();
	Device* Parent;
	virtual ~Coverage();
	virtual bool update()=0;
	virtual std::pair<bool,std::vector<uint64_t>> event()=0;
	virtual std::pair<bool,std::pair<std::string,std::vector<uint64_t>>> get_results()= 0;
	virtual uint32_t get_event(uint32_t id) = 0;
};

// EDIT DISTANCE
class editDistance : public Coverage {
	bool update();
	std::pair<bool,std::vector<uint64_t>> event();
	std::pair<bool,std::pair<std::string,std::vector<uint64_t>>> get_results();
	uint32_t get_event(uint32_t id);
private:
};

uint32_t SV_1D_equality(Assertion* State); //{   //0
// 	std::cout << "1D equality" << std::endl ;
// 	return ALL_OK;
// }

uint32_t SV_1D_inequality(Assertion* State);//{ // 1
	// std::cout << "1D inequality" << std::endl ;
	// return ALL_OK;
// }

uint32_t SV_2D_notequal(Assertion* State); // number 2  , 1000 and 2 // 1002 :(

uint32_t SV_1D_stable(Assertion* State); // number 3  for those playing along at home 

// SV ASSERTIONS
class Assertion{
public:
	Assertion(std::vector<Device*> Devices,uint32_t (*FPTR)(Assertion*),std::vector<uint64_t> Args);
	~Assertion();
	// Store a pointer to parent;
	Device* Parent; // 1D Assertion
	//read up on how to switch between function pointers or how to efficiently write functions
 	uint32_t (*Eval)(Assertion*) = NULL ;
	std::vector<uint64_t> scratchPad;
};

// SV ASSERTIONS
class Assertion2D:public Assertion {
public:
	Assertion2D(std::vector<Device*> Devices,uint32_t (*FPTR)(Assertion*),std::vector<uint64_t> Args);
	~Assertion2D();

	Device* deviceA; 
	Device* deviceB;
};

class SVAssetrions : public Coverage {
public:
	// This parent class of SVA holds the function pointers (vuln point to overflow attacks :P)
	uint32_t add_assertion(std::vector<Device*> Devices,uint32_t type,std::vector<uint64_t> Args);
	bool update() override;
	std::vector<Assertion*> Assertions ;

	// The below seem un necessary
	std::pair<bool,std::vector<uint64_t>> event();
	std::pair<bool,std::pair<std::string,std::vector<uint64_t>>> get_results();
	uint32_t get_event(uint32_t id); // use ID to diff b/w events 
	uint32_t Event0;
// SVA specific containers
	uint32_t (*Eval[SVA_INDEX])(Assertion*)= {SV_1D_equality,SV_1D_inequality,SV_2D_notequal,SV_1D_stable}; // Flexible Array Member at the end of Class
};

// TOGGLE COVERAGE
class ToggleCoverage : public Coverage {
	bool update();
	std::pair<bool,std::vector<uint64_t>> event();
	std::pair<bool,std::pair<std::string,std::vector<uint64_t>>> get_results();
	uint32_t get_event(uint32_t id);
private:
};

#endif