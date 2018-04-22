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
#ifndef Trace_Cache_H
#define Trace_Cache_H


#include <vector>
#include <cstdint>

#include "../TestInstance.hpp"
#define XLEN 64

#if XLEN == 64
    #define INTLEN uint64_t
#else if XLEN == 32 
    #define INTLEN uint32_t
#endif

// TraceFrames
typedef  std::vector<std::pair<INTLEN,INTLEN>> regUpdateFrame;
typedef  std::vector<std::pair<INTLEN,INTLEN>> memUpdateFrame;
typedef  std::pair<regUpdateFrame,memUpdateFrame> traceFrame;


// Should I integrate the trace cache intot he coverage module section  ?? Me thinks yes .

class traceCache{
public:
    riscv ScratchState;
    //traceCache(); // Add back later  ? 
    traceCache(uint32_t max_len);    // ease of use 
    ~traceCache();

    std::vector<traceFrame> Cache;
    uint32_t max_length;
    uint32_t curr_length;
    std::vector<uint64_t> traceCommitMask ; // This restricts the Number of possible coverage trackers to 64
    
    bool configureScratchState();
    bool enqueueTF(traceFrame frame);
    bool commitTopFrame();
    bool commitNFrames(uint32_t N);
};

// my memory footprint is huge, I tbh can at each step compute the net effective state 
    
#endif