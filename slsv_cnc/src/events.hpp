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
#ifndef EVENTS_H
#define EVENTS_H


// This is a list of recognized events in a nice list form to make looking up easier.
// Event is unnecessairly a 32 bit unsigned integer i could have made it shorter , shorter bit width will be useful when slsv is synthasizable and every bit is critical.

// #define vs enums ?? going with #defines for now

/*
        Event Name  {4'h Event Origin,4'h Event ID} 
*/

#define ALL_OK                  0x00000000
#define DEVICE_BASIC_TEST_0     0x10000000
#define DEVICE_BASIC_TEST_1     0x10000001
#define TRACE_CACHE_FULL        0x11111111

#define TO_HOST_0               0x11110000
#define TO_HOST_1               0x11110001
#define TO_HOST_2               0x11110010

#define SVA1D_EQUALITY          0x10100001
#define SVA1D_INEQUALITY        0x10100010

#define SVA2D_EQUALITY          0x10110001
#define SVA2D_INEQUALITY        0x10110010
#define SVA2D_NOTEQUAL          0x10110011

#endif