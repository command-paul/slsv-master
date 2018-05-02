#include "TestInstance.hpp"
#include <vector>

//TODO !! Add Lockstep Run Control

bool LockStep_Verification::addCoverageTracker(){
    return true;
}

bool LockStep_Verification::initialise(){
    return true;
}

bool LockStep_Verification::loadTestVector(){
    return true;
}

bool LockStep_Verification::checkpoint(){
    return true;
}

bool LockStep_Verification::restore(){
    return true;
}

uint32_t LockStep_Verification::run(){
    uint32_t evA = ALL_OK;
    uint32_t evB = ALL_OK;
    while((evA + evB == ALL_OK)){
        // essentially coverage module stuff and return event
        // for(int i = 0 ; i <coverageTrackers.size() ; i ++){
        //     event = coverageTrackers[i]->update();
        //     if(event != ALL_OK) break;
        // }
        evA = deviceA.Bridge->Single_Step();
        evB = deviceB.Bridge->Single_Step();
        deviceA.Cache->updateScratch();
        deviceB.Cache->updateScratch();
        //DUT.Cache->commitScratch(); //get back to this post testing // Noto physically necessary to exist // only needes when checkpointing 
    }
    return evA; // evB
}

