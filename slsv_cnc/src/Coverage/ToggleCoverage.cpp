#include"Coverage.hpp"
#include <iostream>
#include <vector>

// Public Access Status Functions

bool ToggleCoverage::update(){
	return true;
}
std::pair<bool,std::vector<uint64_t>> ToggleCoverage::event(){
	std::pair<bool,std::vector<uint64_t>> a;
	return a;
}
std::pair<bool,std::pair<std::string,std::vector<uint64_t>>> ToggleCoverage::get_results(){
	std::pair<bool,std::pair<std::string,std::vector<uint64_t>>> a;
	return a;
}
uint32_t ToggleCoverage::get_event(uint32_t id){
	return 0;
}

// How is a user supposed to declare these things genuis well your going to have to mask the parent class and make each of these available to wrap in swig,
// additional coverage addition can be worked out later