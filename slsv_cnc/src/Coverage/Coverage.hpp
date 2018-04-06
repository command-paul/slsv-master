#pragma once
#include <vector>
#include <cstdint>
#include <string>

//This is a base class of wrapper functions this defines tha basic interface behind which the different coverafe schemes operate.
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