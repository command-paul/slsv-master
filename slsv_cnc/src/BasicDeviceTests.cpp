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

bool basicDeviceTests::run(){
    // Design abetter run control system and implement
    //loop some some n times or till some event is reached
    //step check if this is an event we care about 
    //gets event from single step is passed upward to the pythn instance for handling
    return true;
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