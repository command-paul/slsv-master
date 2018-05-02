#include"Coverage.hpp"
#include <iostream>
#include <vector>
// Helper functions 

uint32_t SV_1D_equality(Assertion* State){
	if(State->Parent->Cache->ScratchState->HART_Vec[0].PC == 0x80001000) return SVA1D_EQUALITY;
	return ALL_OK;
}

uint32_t SV_1D_inequality(Assertion* State){
	if(State->Parent->Cache->ScratchState->HART_Vec[0].PC > 0x80002000) return SVA1D_INEQUALITY;
	return ALL_OK;
}
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
	Assertions.push_back(new Assertion(Devices[0],Eval[type],Args));
	return ALL_OK;
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

// How is a user supposed to declare these things genuis well your going to have to mask the parent class and make each of these available to wrap in swig,
// additional coverage addition can be worked out later



// Housekeeping for the 1DA class 
Assertion ::Assertion(Device* Parentp,uint32_t (*FPTR)(Assertion*),std::vector<uint64_t> Args){
	Parent = Parentp;
	Eval = FPTR;
	scratchPad = Args;
	return;
}

Assertion ::~Assertion(){
	return;
}

// s