#include "State/State.hpp"
#include <iostream>

// Append all of these to a Vector of test functions.

bool test_spike_interface(){
	return true;
}

bool test_Hart(){
	return true;
}

bool test_memory(){
	return true;
}

bool test_NHSV(){
	return true;
}

int main(){
	riscv* a = new riscv;
	(*a).addHART();
	(*a).addMemory();
	(*a).addNHSV();
	std::cout << (*a).HART_Vec[0].GPR[0] << std::endl;
	// /std::cout << (*a).Memory[0].get_member(0)[0] << std::endl;
	//std::cout << (*a).Memory[0]->address0 << std::endl;
	//std::cout << ((memory*)(*a).Memory[1])->address0 << std::endl;
	//memory* temp = (memory*)&((*a).Memory[1]);
	//std::cout << (*temp).word0 << std::endl;
	//std::cout << ((periphralA*)(*a).Memory[2])->address0 << std::endl;
	//periphralA* temp2 = (periphralA*)&((*a).Memory[2]);
	//std::cout << (*temp2).input0 << std::endl;
	//std::cout << (*(*a).HART_Vec)[0].GPR << std::endl;
	delete a;
}