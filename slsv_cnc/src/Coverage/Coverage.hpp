#include <vector>
#include <cstdint>

//This is a base class of wrapper functions this defines tha basic interface behind which the different coverafe schemes operate.
class Coverage{
public:
	virtual bool update(std::pair<std::vector<uint64_t>,std::vector<uint64_t>>update);
	virtual std::pair<bool,std::vector<uint64_t>> event();
	virtual std::pair<bool,std::pair<std:string,std::vector<uint64_t>>> get_results();
	virtual int get_event(int id);
};

class editDistance : public Coverage {
	bool update(std::pair<std::vector<uint64_t>,std::vector<uint64_t>>update);
	std::pair<bool,std::vector<uint64_t>> event();
	std::pair<bool,std::pair<std:string,std::vector<uint64_t>>> get_results();
	int get_event(int id);
private:
};

class SVAssetrions : public Coverage {
	bool update(std::pair<std::vector<uint64_t>,std::vector<uint64_t>>update);
	std::pair<bool,std::vector<uint64_t>> event();
	std::pair<bool,std::pair<std:string,std::vector<uint64_t>>> get_results();
	int get_event(int id);
private:
};

class ToggleCoverage : public Coverage {
	bool update(std::pair<std::vector<uint64_t>,std::vector<uint64_t>>update);
	std::pair<bool,std::vector<uint64_t>> event();
	std::pair<bool,std::pair<std:string,std::vector<uint64_t>>> get_results();
	int get_event(int id);
private:
};