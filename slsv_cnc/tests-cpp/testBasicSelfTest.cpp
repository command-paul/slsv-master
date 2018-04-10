#include "../src/TestInstance.hpp"
#include <iostream>


int main(){
// Initialise Device
    basicDeviceTests A;
    A.DUT.deviceName = "spike";
    A.DUT.Bridge = new V0 ; 
    A.DUT.DUV = new riscv;


// some 
    A.addCoverageTracker(); //  Add an assert to catch pc = 80000100 to exit;
    // Alternate routine with no coverage routine just running for some specified number of cycles 

    (*((V0*)A.DUT.Bridge)).Initialise();
    (*((V0*)A.DUT.Bridge)).configureV0("0.0.0.0","4444",0,0);
// Pause break to acomodate a special interface for spike only.

// The Interface has been configured The Code below is a prototype for Basic Self Test running.    
    (*((V0*)A.DUT.Bridge)).Single_Step(); 
// Conclude
    return 0;
}