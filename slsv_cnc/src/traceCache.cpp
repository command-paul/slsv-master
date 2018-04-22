#include "TestInstance.hpp"

traceCache::traceCache(){
    return;
}
traceCache::~traceCache(){
    return;   
}

// bool traceCache::configureScratchState(){
//     return true;
// } // Abstract away 

uint32_t traceCache::enqueueTF(traceFrame_t frame){
    if(Cache.size() == max_length) return TRACE_CACHE_FULL;
    Cache.push_back(frame);
    return ALL_OK;
}

uint32_t traceCache::updateScratch(){
    traceFrame_t frame= Cache.back();
    Cache.pop_back();
    return Parent->Cache->ScratchState->updateTraceFrame(frame);
    }


uint32_t traceCache::commitScratch(){
    // co
    return ALL_OK;
    }
