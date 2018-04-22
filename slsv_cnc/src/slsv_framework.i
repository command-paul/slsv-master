%module slsv_framework

%{
/* Header files or functon declaritions here */
#include "../src/TestInstance.hpp"
#import "../src/Interface/Interface.hpp"
#import "../src/Coverage/Coverage.hpp"
#import "../src/State/State.cpp"
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

//%template(regUpdateFrame) std::vector<std::pair<INTLEN,INTLEN>>;
//%template(memUpdateFrame) std::vector<std::pair<INTLEN,INTLEN>>;
//%template(traceFrame) std::pair<regUpdateFrame,memUpdateFrame>;

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
    std::vector<traceFrame> traceCache;
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

