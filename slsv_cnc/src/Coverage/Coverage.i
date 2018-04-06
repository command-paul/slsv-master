%module slsv_coverage
%{
/* Header files or functon declaritions here */
	#include "Coverage.hpp"
%}

%define SWIGWORDSIZE64
%enddef
%include "stdint.i"
%include "std_vector.i"
%include "std_pair.i"
%include "typemaps.i"
%include "std_string.i"

//%template(lop1) std::pair<uint32_t,uint64_t>;
//%template(lop2) std::pair<uint64_t,uint64_t>;
//%template(single_step_ctr) std::pair<std::vector<std::pair<uint32_t,uint64_t>>,std::vector<std::pair<uint64_t,uint64_t>>>;

%template(coverageResult) std::pair<std::string,std::vector<uint64_t>>;
//%template(coverageResultTuple) std::pair<bool,std::pair<std::string,std::vector<uint64_t>>>;
%template(eventVector) std::pair<bool,std::vector<uint64_t>> ;

%template(coverageInputWrongThisIsTemp) std::pair<std::vector<uint64_t>,std::vector<uint64_t>>;

// Coverage - pure virtual
class Coverage{
public:
	Coverage();
	virtual ~Coverage();
	virtual bool update(std::pair<std::vector<uint64_t>,std::vector<uint64_t>>update)=0;
	virtual std::pair<bool,std::vector<uint64_t>> event()=0;
	virtual std::pair<bool,std::pair<std::string,std::vector<uint64_t>>> get_results()= 0;
	virtual int get_event(int id) = 0;
};

class editDistance : public Coverage {
	bool update(std::pair<std::vector<uint64_t>,std::vector<uint64_t>>update);
	std::pair<bool,std::vector<uint64_t>> event();
	std::pair<bool,std::pair<std::string,std::vector<uint64_t>>> get_results();
	int get_event(int id);
private:
};

class SVAssetrions : public Coverage {
	bool update(std::pair<std::vector<uint64_t>,std::vector<uint64_t>>update);
	std::pair<bool,std::vector<uint64_t>> event();
	std::pair<bool,std::pair<std::string,std::vector<uint64_t>>> get_results();
	int get_event(int id);
private:
};

class ToggleCoverage : public Coverage {
	bool update(std::pair<std::vector<uint64_t>,std::vector<uint64_t>>update);
	std::pair<bool,std::vector<uint64_t>> event();
	std::pair<bool,std::pair<std::string,std::vector<uint64_t>>> get_results();
	int get_event(int id);
private:
};