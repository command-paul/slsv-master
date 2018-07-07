#include "V0.hpp"
#include "../Telnet/libtelnet.hpp"

V0::V0(){
	ip = "0.0.0.0";
	port = "0";
	abits = 6;  // for slsv level 0
	width = 64; // Default , TODO Make this a build option
	Transport = new TelnetOCD(ip,port,abits,width);
	// Parent
	return;
}

V0::V0(Device* parentPointer){
	ip = "0.0.0.0";
	port = "0";
	abits = 6;  // for slsv level 0
	width = 64; // Default , TODO Make this a build option
	Transport = new TelnetOCD(ip,port,abits,width);
	Parent =parentPointer;
	return;
}
// Destructor
V0::~V0(){
	delete Transport;
	return;
}
// Initialise 
bool V0::Initialise(){
	(*Transport).Tconnect();
	return true;
}
// Syncronise
// Get it to the defined sync point
// Different policy for multi core
bool V0::Synchronise(){
	return true;
}
// Update State


	// FOR SLSV LEVEL 0 We will have to record everything and then return updates
	// updates based on weather there are any diferences from the current state
	// updates are comitted by test instance
	// This will need a reference to state :P TODO :: add ref to STATE
	//   
	//   // This Is getting cumbersome to type , TODO ::  TYPE DEF THESE STRUCTURES
	//   std::pair<uint32_t,uint64_t> Reg_update_frame ;
	//   //std::pair<uint32_t,uint64_t> Mem_update_frame = std::make_pair(0,0);
	//   std::vector<std::pair<uint32_t,uint64_t>> Reg_update_vector;
	//   std::vector<std::pair<uint64_t,uint64_t>> Mem_update_vector; 
	//   // Single Step
	//   char response[1024]; // Remove this later
	//   (*Transport).runCommand("slsv 2\n",response);
	//   // Capture Updates
	//   uint64_t value;
	//   // just getting GPR`s , PC and FPR for now
	//   for(uint i = 0 ; i < 65 ; i ++){
	//   	(*Transport).getAbstReg(&value,0,i,1,16);
	//   	// Check if this is an update , if not skip // Resolve after reference to state container is sorted
	//   	Reg_update_frame = std::make_pair(i,value);
	//   	Reg_update_vector.push_back(Reg_update_frame);
	//   }
	//   // This is a really big container that im moving around is there anything I can do to make this optimized for usage
	//   // of shared memory between threads ?


// Include a reference to trace cache and the state lib

uint32_t V0::Single_Step(){  // This should return bool and simply set the frame into the trace cache , why even expoose this to the user  
	traceFrame_t updates;
	uint32_t event = ALL_OK; // ref events.hpp	
	char response[1024]; // Remove this later
	//std::cout << "<<<<<<" << std::endl;
	uint32_t iterator = 0;
// 	MEMORY
	UpdateFrame_t MemUpdates;
// 	CSR GPR FPR
	UpdateFrame_t RegUpdates;
	riscv* hartPtr = Parent->Cache->ScratchState;
	// just getting GPR`s , PC and FPR for now
	uint32_t MaxRegs = hartPtr->TopRegAddress;
	uint32_t HartCT  = hartPtr->HART_Vec.size(); // apparently some 2^20 harts now :P 
	// The fetch method does nont currently et the hartsel value 
	for(int HartIter = 0 ; HartIter < HartCT ; HartIter++){
		// GPR FPR
		// Single Step
		(*Transport).runCommand("slsv 2\n",response); // Step Command
		// Capture Updates
		uint64_t value;
		for(uint i = 0 ; i <= MaxRegs; i ++){
			(*Transport).getAbstReg(&value,0,i,1,16);
			// Branching to get the trace cache initialization setup
			// Required to get the latest state setup. // The trace cache state is the main state and the DUV is just a shadow state for house keeping.
			uint64_t csval = hartPtr->get_register(i);
			if(value != csval){
				// Check if this is an update , if not skip // Resolve after reference to state container is sorted
				std::cout << i << "\t" << std::hex << value << "  OLD :: ONDEV   " << std::hex << csval <<std::endl;
				// The I being comitted here needs to be transelated to the required address
				update_t temp = std::make_pair(i,value);
				RegUpdates.push_back(temp);
			}	
	  	}
		// CSR
	}

// 	NHSV
	updates = std::make_pair(RegUpdates,MemUpdates);
	event = Parent->Cache->enqueueTF(updates);
/*	
	If Sate-> cached == Variable read //nothing
	else // Create update and append to the appropriate vector for setting into the trace cache 


	//updates.first = Reg_update_vector; // I suspect this is horribly leaky
	//updates.second = Mem_update_vector;
	// = (traceFrame) std::make_pair(Reg_update_vector,Mem_update_vector);
	*/
	// Partent->traceCache.cache(updates);
	// free updates ?? update and free all liabilities of the interface file ??? -  yasss good in long run as everyone fends for his / her own memory
	std::cout << "<<<<<<" << std::endl;
	return event;
}

// return a vector of updates 
// Access HART & NHSV
std::pair<uint64_t,std::vector<uint32_t>> V0::GetVariable(){
	std::vector<uint32_t> memory = std::vector<uint32_t>(10,0);
	std::pair<uint64_t,std::vector<uint32_t>> a = std::make_pair(true,memory);
	return a;
}
bool V0::SetVariable(){
	return true;
}
// Access Memory
std::pair<uint64_t,std::vector<uint32_t>> V0::GetMemory(){
	std::vector<uint32_t> memory = std::vector<uint32_t>(10,0);
	std::pair<uint64_t,std::vector<uint32_t>> a = std::make_pair(true,memory);
	return a;
}
bool V0::SetMemory(){
	return true;
}
// Load Memory w/ Use Fastest method available to load the program memory 
std::pair<uint64_t,std::vector<uint32_t>> V0::DumpMemory(){
	std::vector<uint32_t> memory = std::vector<uint32_t>(10,0);
	std::pair<uint64_t,std::vector<uint32_t>> a = std::make_pair(true,memory);
	return a;
}
bool V0::LoadBinary(uint64_t address){
	return true;
}
// Checkpoint
// Record the entire accessable state from all reachable DUV`s
bool V0::Checkpoint(std::string File){
	return true;
}
bool V0::Checkpoint(){ // to the already defined checkpoint file :  /
	return true;
}
// Restore
bool V0::Restore(std::string File){
	return true;
}

bool V0::configureV0(std::string IP,std::string PORT,uint32_t ABITS, uint32_t WIDTH){
	ip = IP;
	port = PORT;
	abits = ABITS;
	width = WIDTH;
	(*Transport).set_ip_port(IP,std::stoi(PORT));
	return true;
	}

bool V0::set_ocd_port(uint32_t port){
	return true;
}
bool V0::set_ocd_ip(char* ip){
	return true;
}


// Test Below -- move out of here 
int main(){
	V0 Test = V0();
	Test.configureV0("0.0.0.0","4444",6,64);
	Test.Initialise(); // Propogate No Connection error
	Test.Single_Step(); 
	return 0;
}