%module slsv_interface
%{
/* Header files or functon declaritions here */
	//#include "../src/Interface/Interface.hpp"
	//#include "../src/Interface/V0.hpp"
	//#import "../src/Interface/Telnet/libtelnet.hpp"
	#include "Interface.hpp"
	#include "V0.hpp"
	#import "Telnet/libtelnet.hpp"
%}

%define SWIGWORDSIZE64
%enddef
%include "stdint.i"
%include "std_vector.i"
%include "std_pair.i"
%include "typemaps.i"
%include "std_string.i"

%template(lop1) std::pair<uint32_t,uint64_t>;
%template(lop2) std::pair<uint64_t,uint64_t>;
//%template(single_step_v1) std::vector<std::pair<uint64_t,uint64_t>>;
//%template(single_step_v2) std::vector<std::pair<uint32_t,uint64_t>>;
//%template(single_step) std::pair<single_step_v1,single_step_v2> ;
%template(single_step_ctr) std::pair<std::vector<std::pair<uint32_t,uint64_t>>,std::vector<std::pair<uint64_t,uint64_t>>>;

// Interface - pure virtual
class Interface{
public:
	Interface();
	virtual ~Interface(); 
	virtual bool Initialise() = 0;
	virtual bool Synchronise() = 0;
	virtual std::pair<std::vector<std::pair<uint32_t,uint64_t>>,std::vector<std::pair<uint64_t,uint64_t>>> Single_Step() = 0;
	virtual std::pair<uint64_t,std::vector<uint32_t>> GetVariable() = 0;
	virtual bool SetVariable() = 0;
	virtual std::pair<uint64_t,std::vector<uint32_t>> GetMemory() = 0;
	virtual bool SetMemory() = 0;
	virtual std::pair<uint64_t,std::vector<uint32_t>> DumpMemory() = 0;
	virtual bool LoadBinary(uint64_t address) = 0;
	virtual bool Checkpoint(std::string File) = 0;
	virtual bool Checkpoint() = 0; // to the already defined checkpoint file :/
	virtual bool Restore(std::string File) = 0;
private:

	std::string CheckpointFile;
	bool initialised = 0;
};

// V0
class V0 : public Interface{
public:
    V0();
	~V0() override ;
	bool Initialise()  override;
	bool Synchronise()  override;
	std::pair<std::vector<std::pair<uint32_t,uint64_t>>,std::vector<std::pair<uint64_t,uint64_t>>> Single_Step()  override;
	std::pair<uint64_t,std::vector<uint32_t>> GetVariable()  override;
	bool SetVariable()  override;
	std::pair<uint64_t,std::vector<uint32_t>> GetMemory()  override;
	bool SetMemory()  override;
	std::pair<uint64_t,std::vector<uint32_t>> DumpMemory()  override;
	bool LoadBinary(uint64_t address)  override;
	bool Checkpoint(std::string File)  override;
	bool Checkpoint() override; // to the already defined checkpoint file :  /
	bool Restore(std::string File)  override;
	bool configureV0(std::string IP,std::string PORTS,uint32_t ABITS,uint32_t WIDTH);
//	bool set_ocd_port(uint32_t port);
	//bool set_ocd_ip(char* ip);
};

