#include"Coverage.hpp"
#include <iostream>
#include <vector>

// SVA update policy

bool SVAssetrions::update(){
	// Container to houle all declared L1 Assertions
	// uint32_t iterator = AVector.size();
	// while(iterator > 0){
	// 	type =
	// }
	return ALL_OK;
}
// House Sva DEcls .

// Function pointer to all implements SVA assetrtions 


// EOFP

uint32_t SVA_Equality(bool MN1 , uint64_t address1 ,bool MN2 , uint64_t address2 ){
	return ALL_OK;
}

uint32_t SVA_Equality(bool MN1 , uint64_t address1 ,uint64_t value ){
	return ALL_OK;
}

// Public Access Gneral Purpose Coverage functions

std::pair<bool,std::vector<uint64_t>> SVAssetrions::event(){
	std::pair<bool,std::vector<uint64_t>> a;
	return a;
}
std::pair<bool,std::pair<std::string,std::vector<uint64_t>>> SVAssetrions::get_results(){
	std::pair<bool,std::pair<std::string,std::vector<uint64_t>>> a;
	return a;
}
int SVAssetrions::get_event(int id){
	return 0;
}

// How is a user supposed to declare these things genuis well your going to have to mask the parent class and make each of these available to wrap in swig,
// additional coverage addition can be worked out later