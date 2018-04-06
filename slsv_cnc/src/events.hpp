// This is a list of recognized events in a nice list form to make looking up easier.
// Event is unnecessairly a 32 bit unsigned integer i could have made it shorter , shorter bit width will be useful when slsv is synthasizable and every bit is critical.

// #define vs enums ?? going with #defines for now

/*
        Event Name  {4'h Event Origin,4'h Event ID} 
*/
#define DEVICE_BASIC_TEST_0 0x1000'0000
#define DEVICE_BASIC_TEST_1 0x1000'0001