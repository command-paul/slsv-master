#pragma once
// This is an instance of a device this provides for the iterface to a test instance to operate irrespective of state and interface.
#include "./Interface/Interface.hpp"
#include "./Coverage/Coverage.hpp"
#include "./State/State.hpp"
#include <vector>

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