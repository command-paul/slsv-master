#include "../src/TestInstance.hpp"
#include "../src/Interface/V0.hpp"
#include "../src/Interface/SpikeSlsvIntreface/SpikeIf.hpp"

#include <iostream>


int main(){
// Initialise Device
    basicDeviceTests A;
    A.DUT.deviceName = "spike";
    A.DUT.Cache = new traceCache;
    //A.DUT.DUV = new riscv;
    // The above line is useless this will be a checkpoint on the trace cache scratch state
    // Functionally wrap it out
    //A.DUT.DUV->addHART();
    A.DUT.Cache->ScratchState = new riscv;
    A.DUT.Cache->max_length = 10;
    //A.DUT.DUV->addHART();
    A.DUT.Cache->ScratchState->TopRegAddress = 32;
    A.DUT.Cache->ScratchState->addHART();
    //A.DUT.Cache->ScratchState->addHART();
    A.DUT.Cache->Parent = &(A.DUT);
// some 
    //A.addCoverageTracker(); //  Add an assert to catch pc = 80000100 to exit;
    // Alternate routine with no coverage routine just running for some specified number of cycles 

    //(*((V0*)A.DUT.Bridge)).Initialise();
    // A.DUT.Bridge = new V0; 
    // ((V0*)A.DUT.Bridge)->configureV0("0.0.0.0","4444",0,0);
    // ((V0*)A.DUT.Bridge)->Initialise();
    
    A.DUT.Bridge = new SpikeIf;
    A.DUT.Bridge->Parent = &(A.DUT);
    ((SpikeIf*)A.DUT.Bridge)->setISA("RV64IMAFD");
    ((SpikeIf*)A.DUT.Bridge)->SpikeArguments =("/home/commandpaul/slsv-master/test_vectors/Tests/test" + std::to_string(0) + ".rv64imafd") ;
    ((SpikeIf*)A.DUT.Bridge)->Initialise();
    ((SpikeIf*)A.DUT.Bridge)->Synchronise();
    
// Pause break to acomodate a special interface for spike only.
// The Interface has been configured The Code below is a prototype for Basic Self Test running.    
    A.run();
// Conclude
    return 0;
}