
/*

#include"Coverage.hpp"
#include <iostream>
#include <vector>


// This is an interface to the riscv formal implementations out there right now.

// 1] Framework A :: With the MIT PLV Riscv-semantics with verilog vpi wrappers.

// SVA update policy
bool SVAssetrions::update(){
	for(int i=0;i<Assertions.size();i++){
		Event0 = Assertions[i]->Eval(Assertions[i]);
	}
	return true;
}

// House Sva DEcls .

// add a SVAssertion
uint32_t SVAssetrions::add_assertion(std::vector<Device*> Devices,uint32_t type,std::vector<uint64_t> Args){
	if(type < 1000){
		Assertions.push_back(new Assertion(Devices,Eval[type],Args));
		return ALL_OK;
	}
	else{
		type = type%1000;
		Assertions.push_back(new Assertion2D(Devices,Eval[type],Args));
		return ALL_OK;
	}
}


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
uint32_t SVAssetrions::get_event(uint32_t id){
	if (id==0)return Event0;
	return ALL_OK;
}



// 2] Framework B :: With clifford wolf`s riscv-formal intereface with verilog vpi wrappers.
*/
