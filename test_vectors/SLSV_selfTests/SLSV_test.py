#Starts the test environment & then calls the the respective test scripts 
#TODO Refer to riscv tests -
#I have referenced Riscv tests scalable test class addition mechanism
#I hope to incorporate best practices from its automated logging methodology 
#to the extent necessary for slsv

import threading
import subprocess
import sys

class TestClass():
    def setup(self):
        return True
    def test(self):
        return True
    def getResult(self):
        return True
# This Code jujitsu is to resolve a circulare dependency importing the Test Class into all the test submodule files . 
# I hope to see SLSV self tests to significantly grow in size with the addition of custom modules
# Therefore a tradeoff to allow for more readable code in other modules as instantiated below. 

from testDevice import *   #pylint: disable=W0614
from testInterface import *   #pylint: disable=W0614
from testState import *  #pylint: disable=W0614
from testCoverage import *  #pylint: disable=W0614
from testInterfaceV0 import *  #pylint: disable=W0614

def spawnOcd():
    subprocess.Popen('openocd -f ../spike.cfg'.split(), shell=False)

def spawnSpike():
    OCDThread = threading.Thread(target = spawnOcd)
    OCDThread.start()

class testSpawnOcd(TestClass):
    def setup(self):
        return True
    def test(self):
        return True
    def getResult(self):
        return True

 
# Calling test Vectors - All Test Vectors must return boolean and a string reason of failure and should free all memory possible at the end of the test
# Find all Tests in the imported libraries and run them

def main():
    todo = []
    module = sys.modules[__name__]
    for name in dir(module):
        defn = getattr(module, name)
        if isinstance(defn, type) and hasattr(defn, 'test'):
            todo.append((name, defn))

    for i in range(len(todo)):
        name = todo[i][0]
        definition = todo[i][1]
        instance = definition()
        result = instance.setup()
        result = instance.test()
        result = instance.getResult()
        print("{",name,"}",result)

if __name__ == '__main__':
    sys.exit(main())
