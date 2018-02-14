#include "State/State.hpp"
#include <iostream>

int main(){
	riscv* a = new riscv;
	(*a).addHART();
	(*a).addMemory();
	(*a).addNHSV();
	std::cout << (*a).HART_Vec[0]->GPR << std::endl;
	std::cout << (*a).Memory[0]->address0 << std::endl;
	std::cout << ((memory*)(*a).Memory[1])->address0 << std::endl;
	std::cout << ((memory*)(*a).Memory[1])->word0 << std::endl;
	std::cout << ((periphralA*)(*a).Memory[2])->address0 << std::endl;
	std::cout << ((periphralA*)(*a).Memory[2])->input0 << std::endl;
	//std::cout << (*(*a).HART_Vec)[0].GPR << std::endl;
	delete a;
}