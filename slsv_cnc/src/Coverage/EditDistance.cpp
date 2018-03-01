#import "coverage.hpp"

bool editDistance::update(std::pair<std::vector<uint64_t>,std::vector<uint64_t>>update);
std::pair<bool,std::vector<uint64_t>> editDistance::event();
std::pair<bool,std::pair<std:string,std::vector<uint64_t>>> editDistance::get_results();
int editDistance::get_event();