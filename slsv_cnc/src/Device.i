%module slsv_target
%{
/* Header files or functon declaritions here */
	#include "DeviceInstance.hpp"
	#import "./Interface/Interface.hpp"
	#import "./Coverage/Coverage.hpp"
	#import "./State/State.cpp"
%}
%define SWIGWORDSIZE64
%enddef
%include "stdint.i"
%include "std_vector.i"
%include "std_pair.i"
%include "typemaps.i"

%template(CoverageMetric) std::vector<Coverage>;

class Device{
public:	
	Device();
	~Device();
	riscv DUV;
	Interface Bridge;
	// Somehow make a little vector of all the listed coverage metrics
	std::vector<Coverage> CoverageMetrics;
	std::string deviceName;
};
