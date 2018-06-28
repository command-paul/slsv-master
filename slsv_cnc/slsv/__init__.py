# This is The New Init.py 
# This imports // Conflict etween slsv name and everything else
from slsv.slsv_support import *
#from slsv.slsv_framework import *
from os import system

print("SLSV Framework Vanilla Version 0.0")
print(" X Dynamic Verification Schemes found ")

system('stty sane') # necessary for REPL => because something in the SLSV v0 telnet iterface causes the terminal output formatting to break.
