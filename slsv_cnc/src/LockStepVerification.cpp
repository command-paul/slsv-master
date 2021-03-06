#include "TestInstance.hpp"
#include <omp.h>
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
    uint32_t event = ALL_OK;
    while((evA + evB == ALL_OK)){
        #pragma omp parallel for
        for (int i=0;i<2;i++){ // only to us omp parallel for :/ and not do any confusing thread ID jujitsu
            if (i==0){
                evA = deviceA.Bridge->Single_Step();
                deviceA.Cache->updateScratch();
            }
            if (i==1){
                evB = deviceB.Bridge->Single_Step();
                deviceB.Cache->updateScratch();
           }
        }        
        for(int i = 0 ; i < coverageTrackers.size() ; i ++){
            if(coverageTrackers[i]->update()) event = coverageTrackers[i]->get_event(0);
            if(event != ALL_OK) return event;
        }
        //DUT.Cache->commitScratch(); //get back to this post testing // Noto physically necessary to exist // only needes when checkpointing 
    }
    return evA; // evB
}

