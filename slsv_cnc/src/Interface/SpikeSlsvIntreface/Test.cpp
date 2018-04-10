// Tests for SpikeIf
#include "Interface.hpp"
#include "SpikeIf.hpp"

#define TEST_CYCLES 10

int main(){
    SpikeIf testbench;
    // Configure 
    testbench.setISA("RV64IMAFD");
    testbench.Initialise();
    // Initialse
    //Run
    int test_cycle = 0; 
    while(test_cycle < TEST_CYCLES){
        //Step
        //Print Something
        test_cycle--;
       }
    // Conclude and cleanup .
    return 0;
}