#include "./Interface/Interface.hpp"
#include "./Interface/V0.hpp" // Rework this to something better
#include "./Coverage/Coverage.hpp"
#include "./State/State.hpp"
#include "events.hpp"
#include <vector>

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

