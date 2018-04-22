// Tests for SpikeIf
#include "Interface.hpp"
#include "SpikeIf.hpp"

#define TEST_COUNT 10
#define TEST_CYCLES 10

int main(){
    int test_counter = 0;
    SpikeIf* testbench ;
    std::pair<std::vector<std::pair<uint32_t,uint64_t>>,std::vector<std::pair<uint64_t,uint64_t>>> A;
    while(test_counter < TEST_COUNT){
        // Configure 
        testbench = new SpikeIf();
        testbench->setISA("RV64IMAFD");
        testbench->SpikeArguments =("/home/commandpaul/slsv-master/test_vectors/Tests/test" + std::to_string(test_counter) + ".rv64imafd") ;
        testbench->Initialise();
        // Initialse
        testbench->Synchronise();

        int test_cycle = 0;
        while(test_cycle < TEST_CYCLES){
            //A = testbench->Single_Step();
            test_cycle++;
            //free(&A);
           }
        // Conclude and cleanup .
        delete testbench;
        test_counter ++;
    }
    return 0;
}