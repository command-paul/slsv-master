#include "DumParser.hpp"

#include <iostream>     // std::cout
#include <fstream>      // std::ifstream


/* // Reference Decl
class DumParser : public Interface{
public:
    // Constructors
    DumParser();
	DumParser(Device* parentPointer);
	// Destructor
    ~DumParser() override ;
	// Initialise 
	bool Initialise()  override;
	// Syncronise
	// Get it to the defined sync point
	// Different policy for multi core
	bool Synchronise()  override;
	// Update State
	uint32_t Single_Step()  override;
	
	bool Set_Stream(std::string pathtofd);
private:
	std::string path;
	FILE* TraceStream;
};
*/

DumParser::DumParser(){
	path = "";
	TraceStream = NULL;
	return;
}

DumParser::DumParser(Device* parentPointer){
	path = "";
	TraceStream = NULL;
	Parent =parentPointer;
	return;
}
// Destructor
DumParser::~DumParser(){
	if (TraceStream != NULL) TraceStream.close(); 
	return;
}
// Initialise 
bool DumParser::Initialise(){
	//open file
	TraceStream = std::ifstream(path, std::ifstream::binary);
	if (!TraceStream)return false;
	return true;
}

// Syncronise
// Get it to the defined sync point
// Different policy for multi core
bool DumParser::Synchronise(uint64_t){
	while ( Parent->State-> pc ! = 0x80000000 ; 
	Single_Step();
	return true;
}

// Update State
	// For DumpParseing we read the transmitted trace and proceed to filter the same 
	// for being acted upon by subsequent layers of SLSV

// Include a reference to trace cache and the state lib

	// Better comparison Updates at this stage are packed with the timestamp :/
	// packet Format 16 bytes - can be optimised down later This is a lot of over head . that will have to be eliminated when this is refined as a reciever for a data trace unit.
	// REGISTER
	// Bytes 16 - 13 :: 32 BIT Sequence Number and Memory / Register Flag BIt // this is discarded after receipt.
	// Bytes 12 -  9 :: 32 BIT HART ID :: State ID REgister Identifier.
	// Bytes 8  -  0 :: 64 BIT Value Update
	// MEMORY
	// Bytes 16 - 13 :: 32 BIT Sequence Number and Memory / Register Flag BIt // this is discarded after receipt.
	// Bytes 12 -  5 :: 64 BIT Address
	// Bytes 4  -  0 :: 32 BIT Value
	// This is very  Very REdundant and can very significantly be optimized.
	// DONT USE THIS IN PRODUCTION WHILE IS NOT OPTIMIZED

uint32_t DumParser::Single_Step(){  // This should return bool and simply set the frame into the trace cache , why even expoose this to the user  
	
	// Read a frame from the file
	//char buffer[12];
	
	uint128_t buffer = 0; // I Have a reason to believe that working with such arethemetic may be a better container to work with .
	traceFrame_t updates;
	uint32_t event = ALL_OK; // ref events.hpp	
	UpdateFrame_t RegUpdates;
	
	UpdateFrame_t MemUpdates;
	riscv* hartPtr = Parent->Cache->ScratchState;
	// just getting GPR`s , PC and FPR for now
	uint32_t MaxRegs = hartPtr->TopRegAddress;
	uint32_t HartCT  = hartPtr->HART_Vec.size(); // apparently some 2^20 harts now :P 

	uint64_t address = 0;
	uint64_t value = 0;


	TraceStream.read (buffer,16);
	while( (TraceStream) && (buffer != 0xFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF) ) {
		if (TraceStream.gcount() != 16){// the number of bytes actually read in the last read operationA 
			uint32_t seqno = (uint32_t)((buffer & 0xFFFFFFFE000000000000000000000000 ) >> 97)
			std::cout << "Recieved Sequence Number "
			if ((buffer & 0x00000001000000000000000000000000) > 0 ){
				address = (uint64_t)((buffer & 0x00000000FFFFFFFFFFFFFFFF00000000 ) >> 32)
				value = = (uint32_t)( buffer & 0x000000000000000000000000FFFFFFFF )
				//append packet to vector
				}
			else{
				address = (uint32_t)((buffer & 0x00000000FFFFFFFF0000000000000000 ) >> 64)
				uint64_t csval = 0; //hartPtr->get_register(address);
				value = = (uint64_t)( buffer & 0x0000000000000000FFFFFFFFFFFFFFFF )
				if(value != csval)
					std::cout << i << "\t" << std::hex << value << "  OLD :: ONDEV   " << std::hex << csval <<std::endl;
					//append packet to vector
					update_t temp = std::make_pair(i,value);
					RegUpdates.push_back(temp);
				}
			}	
		TraceStream.read(buffer,16);
		}	
	updates = std::make_pair(RegUpdates,MemUpdates);
	event = Parent->Cache->enqueueTF(updates);
	return event;
	}

bool DumParser::Set_Stream(std::string pathtofd){
	path =	pathtofd;
	return true;
}


// Test Below -- move out of here 
int main(){
	DumParser Test = DumParser();
	Test.configureV0("0.0.0.0","4444",6,64);
	Test.Initialise(); // Propogate No Connection error
	Test.Single_Step(); 
	return 0;
}