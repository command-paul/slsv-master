%module slsv_coverage
%{
/* Header files or functon declaritions here */
    #include "Coverage.hpp"
%}

class riscv;
class Assertion;
class Device; // Forward declarition

typedef  std::pair<INTLEN,INTLEN> update_t;
typedef  std::vector<update_t> UpdateFrame_t;
typedef  std::pair<UpdateFrame_t,UpdateFrame_t> traceFrame_t;

// Should I integrate the trace cache intot he coverage module section  ?? Me thinks yes .
class traceCache{
public:
    riscv* ScratchState; 
	// The above is my sacraficeing space for commputational overhead  time to functional deployment
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
    bool configureScratchState();
    uint32_t enqueueTF(traceFrame_t frame);
    bool commitTopFrame();
    bool commitNFrames(uint32_t N);
	uint32_t updateScratch();
	uint32_t commitScratch();
};

// my memory footprint is huge, I tbh can at each step compute the net effective state 
    
class Coverage{
public:
	Coverage();
	Device* Parent;
	virtual ~Coverage();
	virtual bool update()=0;
	virtual std::pair<bool,std::vector<uint64_t>> event()=0;
	virtual std::pair<bool,std::pair<std::string,std::vector<uint64_t>>> get_results()= 0;
	virtual uint32_t get_event(uint32_t id) = 0;
};

// EDIT DISTANCE
class editDistance : public Coverage {
	bool update();
	std::pair<bool,std::vector<uint64_t>> event();
	std::pair<bool,std::pair<std::string,std::vector<uint64_t>>> get_results();
	uint32_t get_event(uint32_t id);
private:
};


class SVAssetrions : public Coverage {
public:
	// This parent class of SVA holds the function pointers (vuln point to overflow attacks :P)
	uint32_t add_assertion(std::vector<Device*> Devices,uint32_t type,std::vector<uint64_t> Args);
	bool update() override;
	std::vector<Assertion*> Assertions ;

	// The below seem un necessary
	std::pair<bool,std::vector<uint64_t>> event();
	std::pair<bool,std::pair<std::string,std::vector<uint64_t>>> get_results();
	uint32_t get_event(uint32_t id); // use ID to diff b/w events 
	uint32_t Event0;
// SVA specific containers
//	uint32_t (*Eval[SVA_INDEX])(Assertion*)= {SV_1D_equality,SV_1D_inequality}; // Flexible Array Member at the end of Class
};

// TOGGLE COVERAGE
class ToggleCoverage : public Coverage {
	bool update();
	std::pair<bool,std::vector<uint64_t>> event();
	std::pair<bool,std::pair<std::string,std::vector<uint64_t>>> get_results();
	uint32_t get_event(uint32_t id);
private:
};