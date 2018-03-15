

%module slsv_interface
%{
/* Header files or functon declaritions here */
	#include "Interface.hpp"
	#include "V0.hpp"
	#import "./Telnet/libtelnet.hpp"
%}
%define SWIGWORDSIZE64
%enddef
%include "stdint.i"
%include "std_vector.i"
%include "std_pair.i"
%include "typemaps.i"
%include "std_string.i"
// %template(Tester1) std::vector <uint32_t>;
// %template(TestRet) std::pair<bool,std::vector <uint32_t>>;
// %template(HartVector) std::vector <risc_v_HART> ;
// %template(MemVector0) std::vector <memoryMappedDevice> ;
// %template(IntVec) std::vector <int> ;
// %template(NHSVVector) std::vector <nonHARTStateVariables> ;




// Interface

class Interface{
// 	public:
// 		Interface();
// 		virtual ~Interface();
// 		virtual bool Initialise();
// 		virtual bool Synchronise();
// 		virtual std::vector<std::pair<uint64_t,uint64_t>> Single_Step();
// 		virtual std::pair<uint64_t,std::vector<uint32_t>> GetVariable();
// 		virtual bool SetVariable();
// 		virtual std::pair<uint64_t,std::vector<uint32_t>> GetMemory();
// 		virtual bool SetMemory();
// 		virtual std::pair<uint64_t,std::vector<uint32_t>> DumpMemory();
// 		virtual bool LoadBinary(uint64_t address);
// 		virtual bool Checkpoint(std::string File);
// 		virtual bool Checkpoint(); // to the already defined checkpoint file :/
// 		virtual bool Restore(std::string File);
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

