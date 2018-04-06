#include "../src/State/State.hpp"
#include "../src/Interface/Interface.hpp"
#include <iostream>

// Append all of these to a Vector of test functions.

bool test_spike_interface(){
	return true;
}

bool test_state(){
	riscv* a = new riscv;
	(*a).addHART();
	(*a).addMemory();
	(*a).addNHSV();
	std::cout << (*a).HART_Vec[0].GPR[0] << std::endl;
	delete a;
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
bool test_Device(){
	return true;
}

int main(){
	bool test_result = false;
	test_result = test_Device();
	return (int)test_result;
}