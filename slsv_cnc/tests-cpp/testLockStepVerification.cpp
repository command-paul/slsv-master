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
#include "../src/Interface/V0.hpp"
#include "../src/Interface/SpikeSlsvIntreface/SpikeIf.hpp"

#include <iostream>


int main(){
// Initialise Device
    LockStep_Verification A;
    A.deviceA.deviceName = "spikeOpenOCD"; 
    A.deviceB.deviceName = "spike";
    A.deviceA.Cache = new traceCache;
    A.deviceB.Cache = new traceCache;

    A.deviceA.Cache->ScratchState = new riscv;
    A.deviceA.Cache->max_length = 10;
    A.deviceA.Cache->ScratchState->TopRegAddress = 32;
    A.deviceA.Cache->ScratchState->addHART();
    A.deviceA.Cache->Parent = &(A.deviceA);
    A.deviceB.Cache->ScratchState = new riscv;
    A.deviceB.Cache->max_length = 10;
    A.deviceB.Cache->ScratchState->TopRegAddress = 32;
    A.deviceB.Cache->ScratchState->addHART();
    A.deviceB.Cache->Parent = &(A.deviceB);

    A.deviceA.Bridge = new V0; 
    A.deviceA.Bridge->Parent = &(A.deviceA);
    ((V0*)A.deviceA.Bridge)->configureV0("0.0.0.0","4444",0,0);
    ((V0*)A.deviceA.Bridge)->Initialise();
    ((V0*)A.deviceA.Bridge)->Synchronise();

    A.deviceB.Bridge = new SpikeIf;
    A.deviceB.Bridge->Parent = &(A.deviceB);
    ((SpikeIf*)A.deviceB.Bridge)->setISA("RV64IMAFD");
    ((SpikeIf*)A.deviceB.Bridge)->SpikeArguments =("/home/commandpaul/slsv-master/test_vectors/Tests/test" + std::to_string(0) + ".rv64imafd") ;
    ((SpikeIf*)A.deviceB.Bridge)->Initialise();
    ((SpikeIf*)A.deviceB.Bridge)->Synchronise();
    
// Pause break to acomodate a special interface for spike only.
// The Interface has been configured The Code below is a prototype for Basic Self Test running.    
    A.run();
// Conclude
    return 0;
}