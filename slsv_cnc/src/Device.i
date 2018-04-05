%module slsv_target
%{
/* Header files or functon declaritions here */
#include "../src/DeviceInstance.hpp"
#import "../src/Interface/Interface.hpp"
#import "../src/Coverage/Coverage.hpp"
#import "../src/State/State.cpp"
%}
%define SWIGWORDSIZE64
%enddef
%include "stdint.i"
%include "std_vector.i"
%include "std_pair.i"
%include "typemaps.i"

%include "Interface/Interface.i"
%include "State/State.i"


class Device{
public:	
	Device();
	~Device();
	riscv* DUV;
	Interface* Bridge;
	// Somehow make a little vector of all the listed coverage metrics
	std::string deviceName;
};


