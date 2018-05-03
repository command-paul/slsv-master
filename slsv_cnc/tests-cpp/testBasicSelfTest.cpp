/*-------------------------------------------------------------------------------------------------- 
* Copyright (c) 2018, IIT Madras All rights reserved.
* 
* Redistribution and use in source and binary forms, with or without modification, are permitted
* provided that the following conditions are met:
* 
* - Redistributions of source code must retain the below copyright notice, this list of conditions
*   and the following disclaimer.  
* - Redistributions in binary form must reproduce the above copyright notice, this list of 
*   conditions and the following disclaimer in the documentation and/or other materials provided 
*   with the distribution.  
* - Neither the name of IIT Madras  nor the names of its contributors may be used to endorse or 
*   promote products derived from this software without specific prior written permission.
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
* AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
* CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
* IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
* OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* --------------------------------------------------------------------------------------------------
* Author:  Paul George
* Email id: pg456@snu.edu.in
* ------------------------------------------------------------------------------------------------*/

#include "../src/TestInstance.hpp"
#include "../src/Interface/V0/V0.hpp"
#include "../src/Interface/SpikeSlsvIntreface/SpikeIf.hpp"

#include <iostream>

#define CHECKPROPS 1000

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
    
    A.coverageTrackers.push_back(new SVAssetrions);
    
    // Test for increased comutational latency because of adding state trackers
    
    for(int itr = 0 ;itr <CHECKPROPS;itr++){
        ((SVAssetrions*)A.coverageTrackers[0])->add_assertion({&(A.DUT)},1,{0,0,0,0});
    }
    ((SVAssetrions*)A.coverageTrackers[0])->add_assertion({&(A.DUT)},0,{0,0,0,0});
    //((SVAssetrions*)A.coverageTrackers[0])->update();
    //((SVAssetrions*)A.coverageTrackers[0])-> ; 

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