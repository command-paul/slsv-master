%module slsv_framework

%{
/* Header files or functon declaritions here */
#include "../src/TestInstance.hpp"
#include "Commons.hpp"
%}

%define SWIGWORDSIZE64
%enddef
%include "stdint.i"
%include "std_vector.i"
%include "std_pair.i"
%include "typemaps.i"

%include "Interface/Interface.i"
%include "State/State.i"
%include "Coverage/Coverage.i"
%template(ct_vec) std::vector<Coverage*>;

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