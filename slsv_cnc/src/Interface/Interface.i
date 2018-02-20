/* Interface file for State.cpp 
%include <std_string.i>
*/


%module slsv_interface
%{
/* Header files or functon declaritions here */
	#include "Interface.hpp"
%}
%define SWIGWORDSIZE64
%enddef
%include "stdint.i"
%include "std_vector.i"
%include "std_pair.i"
%include "typemaps.i"

// %template(Tester1) std::vector <uint32_t>;
// %template(TestRet) std::pair<bool,std::vector <uint32_t>>;
// %template(HartVector) std::vector <risc_v_HART> ;
// %template(MemVector0) std::vector <memoryMappedDevice> ;
// %template(IntVec) std::vector <int> ;
// %template(NHSVVector) std::vector <nonHARTStateVariables> ;
