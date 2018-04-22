#include"TestInstance.hpp"

bool basicDeviceTests::initialise(){
    return true;
    }

bool basicDeviceTests::testInterfaces(){
    return true;
    }

bool basicDeviceTests::testRegisters(){
    return true;
    }

bool basicDeviceTests::testMemory(){
    return true;
    }

uint32_t basicDeviceTests::run(){
    uint32_t event = ALL_OK;
    while((event  = DUT.Bridge->Single_Step()) == ALL_OK){
        // essentially coverage module stuff and return event
        for(int i = 0 ; i <coverageTrackers.size() ; i ++){
            event = coverageTrackers[i]->update();
            if(event != ALL_OK) break;
        }
        DUT.Cache->updateScratch();
        //DUT.Cache->commitScratch(); //get back to this post testing // Noto physically necessary to exist // only needes when checkpointing 
    }
    //handle single step error or num run expired 

    return event; // or the run cycles expired all ok eqv 
    }

bool basicDeviceTests::checkpoint(){
    return true;
    }

bool basicDeviceTests::restore(){
    return true;
    }

bool basicDeviceTests::addCoverageTracker(){
    return true;
    }

bool step(){

    // Design abetter run control system and implement
    //error = deviceA tracecache(deviceSingle step);
    //if (error) print error type;
    //event = Coverage Evaluate();
    bool event;
    return event;
    }