# This is a Test SLSV - self validation routine.
# Starts the test environment & then calls the the respective test scripts 

# TODO Refer to riscv tests -

import threading
import subprocess

def spawnOcd():
    Process = subprocess.Popen('openocd -f ../spike.cfg'.split(),shell=False)

def spawnSpike():
    OCDThread = threading.Thread(target = spawnOcd)

class TestClass():
    def setup(self):
        return True
    def run(self):
        return True
    def getResult(self):
        return True

# RISCV tests describes calss es of test objects which each test derives and then implements custom methods of

# B

# 
# Calling test Vectors - All Test Vectors must exit 0 and should free all memory possible at the end of the test
# ^ are SLSV Validation tests

# basic sanity for communication error detect and termination