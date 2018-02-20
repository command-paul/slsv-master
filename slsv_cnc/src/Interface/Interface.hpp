// This is the Interface Header file for the SLSV CNC Server

/*
	This file essentially provides a bunnch of methods to the parent Device and test instance sets 
	the methds being provided as wrappers to the entire library of the access versions for V0 - V5
*/

// This provides the most crude access interface 
// Access policies will have to be defined inside each of the 
// Version files

// Syncronise
// Get it to the defined sync point
// Different policy for multi core


// Update State
// return a vector of updates 

// Access HART

// Access NHSV

// Access Memory

// Load Memory
// Use Fastest method available to load the program memory 

// Checkpoint
// Record the entire accessable state from all reachable DUV`s

// Restore
// Restore the checkpoint state to the core and set/reset state variables as defined by user.
