# This is a Test SLSV - self validation routine.
# Starts the test environment & then calls the the respective test scripts 

# TODO Refer to riscv tests - this spawns many threads of Lock Step Testinstances collateing coverage data at the end of each test.

#import threading
#import subprocess

#def spawnOcd():
#    Process = subprocess.Popen('openocd -f ../spike.cfg'.split(),shell=False)

#def spawnSpike():
#    OCDThread = threading.Thread(target = spawnOcd)

#class TestClass():
#    def setup(self):
#        return True
#    def run(self):
#        return True
#    def getResult(self):
#        return True

import subprocess

from slsv import slsv_framework as sf
from slsv import slsv_support as ss
import time
import signal # for handling signals later not being used now :/

# TODO Handle SIG-INT in a pretty way of checkpointing everything


def BasicSelfTests(path,telnet_port1,telnet_port2):
    A = sf.basicDeviceTests()
    A.DUT.deviceName = "spikeOpenOCD"
    A.DUT.Cache = sf.traceCache()

    A.DUT.Cache.ScratchState = sf.riscv()
    A.DUT.Cache.max_length = 10
    A.DUT.Cache.ScratchState.TopRegAddress = 32
    A.DUT.Cache.ScratchState.addHART()
    A.DUT.Cache.Parent = A.DUT
    
    DABV0 = sf.V0()
    DABV0.Parent = A.DUT
    DABV0.configureV0("0.0.0.0",telnet_port2,0,0);
    
    #DAB = sf.SpikeIf()
    #DAB.Parent = A.deviceA
    #DAB.setISA("RV64IMAFD")
    #DAB.SpikeArguments =(path) 
    
    #A.deviceA.Bridge = DAB
    A.DUT.Bridge = DABV0
    SVA = sf.SVAssetrions()
    config  = [0,0,0,0]
    dv = [A.DUT]
    config  = [0x80000360]
    SVA.add_assertion([dv[0]],0,config)
    config  = [0x80000048]
    SVA.add_assertion([dv[0]],0,config)
    A.coverageTrackers.push_back(SVA)

    A.DUT.Bridge.Initialise()
    A.DUT.Bridge.Synchronise()
    
    event = 0
     
    while event == 0x0 :
        event = A.run()
        print(A.DUT.Cache.ScratchState.HART_Vec[0].PC)
        # Code here for event handler , replaces catching the return value of A.Run
    print("Exiting Test with event",format(event, '#x'))
    return

def LockstepVerification(path,telnet_port1,telnet_port2):
    A = sf.LockStep_Verification()
    A.deviceA.deviceName = "spikeOpenOCD"
    A.deviceB.deviceName = "spike"
    A.deviceA.Cache = sf.traceCache()
    A.deviceB.Cache = sf.traceCache()
    
    A.deviceA.Cache.ScratchState = sf.riscv()
    A.deviceA.Cache.max_length = 10
    A.deviceA.Cache.ScratchState.TopRegAddress = 32
    A.deviceA.Cache.ScratchState.addHART()
    A.deviceA.Cache.Parent = A.deviceA
    A.deviceB.Cache.ScratchState = sf.riscv()
    A.deviceB.Cache.max_length = 10
    A.deviceB.Cache.ScratchState.TopRegAddress = 32
    A.deviceB.Cache.ScratchState.addHART()
    A.deviceB.Cache.Parent = A.deviceB
    
    DABV0 = sf.V0()
    DABV0.Parent = A.deviceA
    DABV0.configureV0("0.0.0.0",telnet_port1,0,0);    
    DBBV0 = sf.V0()
    DBBV0.Parent = A.deviceB
    DBBV0.configureV0("0.0.0.0",telnet_port2,0,0);
    #DAB = sf.SpikeIf()
    #DAB.Parent = A.deviceA
    #DAB.setISA("RV64IMAFD")
    #DAB.SpikeArguments =(path) 
    #DBB = sf.SpikeIf()
    #DBB.Parent = A.deviceB
    #DBB.setISA("RV64IMAFD")
    #DBB.SpikeArguments =(path)
    #A.deviceA.Bridge = DAB
    #A.deviceB.Bridge = DBB
    A.deviceA.Bridge = DABV0
    A.deviceB.Bridge = DBBV0
    # '''    
    SVA = sf.SVAssetrions()
    config  = [0,0,0,0]
    dv = [A.deviceA,A.deviceB]
    SVA.add_assertion(dv,1002,config)
    #A.coverageTrackers.push_back(SVA)
    #SVA2 = sf.SVAssetrions()
    #config2  = [0,0,0,0]
    #dv2 = [A.deviceA]
    #SVA2.add_assertion(dv2,1,config2)
    #A.coverageTrackers.push_back(SVA2)
    #SVA1 = sf.SVAssetrions()
    #config1  = [0,0,0,0]
    #dv1 = [A.deviceA]
    ##SVA1.add_assertion(dv1,1,config1)
    #SVA1.add_assertion(dv1,3,config1)
    #A.coverageTrackers.push_back(SVA1)
    SVA = sf.SVAssetrions()
    config  = []
    dv = [A.deviceA,A.deviceB]
    #SVA.add_assertion(dv,1002,config)
    config  = [0x80000360]
    SVA.add_assertion([dv[0]],0,config)
    config  = [0x80000048]
    SVA.add_assertion([dv[0]],0,config)
    #config  = []
    #SVA.add_assertion([dv[0]],3,config)
    A.coverageTrackers.push_back(SVA)
    A.deviceA.Bridge.Initialise()
    A.deviceB.Bridge.Initialise()
    A.deviceA.Bridge.Synchronise()
    A.deviceB.Bridge.Synchronise()

    event = 0
    while event == 0x0 :
        event = A.run()
        print(A.deviceB.Cache.ScratchState.HART_Vec[0].PC)
        # Code here for event handler , replaces catching the return value of A.Run
    print("Exiting Test with event",format(event, '#x'))
    #DAB.destroy_s() # Spike Instance
    #DBB.destroy_s() # Spike Instance
    return


def DLockstepVerification(path):
    bootstrap_path = '/scratch/slsv-master/test_vectors/bootstrap/output.riscv'

    # Port 1 is the shakti C-class default settings
    OOCD_port1 = '10000'
    config_file1 = '/scratch/slsv-master/test_vectors/spike.cfg'
    ip1 = '0.0.0.0'
    tcl_port1 = '6666'
    gdb_port1 = '3333'
    telnet_port1 = '4444'

    # Alternate Settings
    OOCD_port2 = '10001'
    config_file2 = '/scratch/slsv-master/test_vectors/spike.cfg'
    ip2 = '0.0.0.0'
    tcl_port2 = '6667'
    gdb_port2 = '3334'
    telnet_port2 = '4445'

    #process1 = ss.SpawnSpikeV0(bootstrap_path,OOCD_port1)
    #process1 = ss.SpawnShaktiV0()
    #process2 = ss.SpawnSpikeV0(bootstrap_path,OOCD_port2)
    #Kewl = input("Check Spike V0 Spawned")
    #process3 = ss.SpawnOOCD(config_file1,ip1,OOCD_port1,tcl_port1,gdb_port1,telnet_port1)
    #time.sleep(0.5)
    #process4 = ss.SpawnOOCD(config_file2,ip2,OOCD_port2,tcl_port2,gdb_port2,telnet_port2)
    #Kewl = input("Check OOCD V0 Spawned")
    time.sleep(5)
    ss.SpawnGDBLoadKill(ip1,gdb_port1,path)
    ss.SpawnGDBLoadKill(ip2,gdb_port2,path)
    #Kewl = input("Check GDB LOADED Spawned")
    LockstepVerification(path,telnet_port1,telnet_port2)
    #windup test env 
    #process1.kill()
    #process2.kill()
    #process3.kill()
    #process4.kill()

def DBasicSelfTests(path):
    bootstrap_path = '/scratch/slsv-master/test_vectors/bootstrap/output.riscv'

    # Port 1 is the shakti C-class default settings
    OOCD_port1 = '10000'
    config_file1 = '/scratch/slsv-master/test_vectors/cfpga.cfg'
    ip1 = '0.0.0.0'
    tcl_port1 = '6666'
    gdb_port1 = '3333'
    telnet_port1 = '4444'
    # Alternate Settings
    OOCD_port2 = '10001'
    config_file2 = '/scratch/slsv-master/test_vectors/spike.cfg'
    ip2 = '0.0.0.0'
    tcl_port2 = '6667'
    gdb_port2 = '3334'
    telnet_port2 = '4445'
    #process2 = ss.SpawnShaktiV0()
    #process2 = ss.SpawnSpikeV0(bootstrap_path,OOCD_port2)
    #process4 = ss.SpawnOOCD(config_file1,ip1,OOCD_port1,tcl_port1,gdb_port1,telnet_port1)
    #process4 = ss.SpawnOOCD(config_file2,ip2,OOCD_port2,tcl_port2,gdb_port2,telnet_port2)
    
    #ss.SpawnGDBLoadKill(ip2,gdb_port1,path)
    p1 = subprocess.Popen('riscv64-unknown-elf-gdb', stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    #ip   = '0.0.0.0'
    #port = '3333'
    ip = ip1
    port = gdb_port1
    message = ('target remote '+ ip + ':' + port + ' \n').encode()
    p1.stdin.write(message)
    p1.stdin.flush()
    time.sleep(2)
    message = ('load '+path+' \n').encode()
    p1.stdin.write(message)
    p1.stdin.flush()
    time.sleep(5)
    p1.stdin.write('quit \n'.encode())
    p1.stdin.flush()
    p1.kill()
    BasicSelfTests(path,telnet_port1,telnet_port1)
    #BasicSelfTests(path,telnet_port2,telnet_port2)
    #process2.kill()
    #process4.kill()

count = 0
TD  = ss.TestDispatch()
#Tests = TD.getTests('/scratch/slsv-master/test_vectors/Tests/','')
Tests = TD.getTests('/scratch/slsv-master/test_vectors/tests')
#while True :

for Test in Tests:
    path = Test[0]
    print (path)
    count=count+1
    DLockstepVerification(path)
    #DBasicSelfTests(path)


print (count," /122 Tests Cmpleted ! check to_host for status")
