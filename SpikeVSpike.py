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

from slsv import slsv_framework as sf


def BasicSelfTests():
    A = sf.basicDeviceTests()
    A.DUT.deviceName = "Spike"
    #basicDeviceTests A;
    A.DUT.deviceName = "spike";
    A.DUT.Cache = sf.traceCache();
    #A.DUT.DUV = new riscv;
    #The above line is useless this will be a checkpoint on the trace cache scratch state
    #Functionally wrap it out
    #A.DUT.DUV->addHART();
    A.DUT.Cache.ScratchState = sf.riscv()
    A.DUT.Cache.max_length = 10;
    #A.DUT.DUV->addHART();
    A.DUT.Cache.ScratchState.TopRegAddress = 32;
    A.DUT.Cache.ScratchState.addHART();
    #A.DUT.Cache->ScratchState->addHART();
    #A.DUT.Cache.Parent = A.DUT ;
    #(*((V0*)A.DUT.Bridge)).Initialise();
    #A.DUT.Bridge = new V0; 
    #((V0*)A.DUT.Bridge)->configureV0("0.0.0.0","4444",0,0);
    #((V0*)A.DUT.Bridge)->Initialise();

    #A.DUT.Bridge = sf.SpikeIf();
    #A.DUT.Bridge.Parent = A.DUT;

    SVA = sf.SVAssetrions()
    config  = [0,0,0,0]
    dv = [A.DUT,A.DUT,A.DUT]
    SVA.add_assertion(dv,0,config)
    #A.coverageTrackers.push_back(SVA)

    SVA1 = sf.SVAssetrions()
    config1  = [0,0,0,0]
    dv1 = [A.DUT,A.DUT,A.DUT]
    SVA1.add_assertion(dv1,1,config1)
    A.coverageTrackers.push_back(SVA1)

    #A.coverageTrackers[0].add_assertion({A.DUT},1,{0,0,0,0});
    A.DUT.Bridge.__class__ = sf.SpikeIf
    #A.DUT.Bridge.setISA("RV64IMAFD")
    A.DUT.Bridge.SpikeArguments =("/home/commandpaul/slsv-master/test_vectors/Tests/test" + str(0) + ".rv64imafd") ;
    A.DUT.Bridge.Initialise()
    A.DUT.Bridge.Synchronise()
    event = A.run()
    print("Run exited with ",format(event, '#x'))

def LockstepVerification():
    A = sf.LockStep_Verification()
    A.deviceA.deviceName = "spikeOpenOCD"; 
    A.deviceB.deviceName = "spike";
    A.deviceA.Cache = sf.traceCache()
    A.deviceB.Cache = sf.traceCache()
    
    A.deviceA.Cache.ScratchState = sf.riscv()
    A.deviceA.Cache.max_length = 10;
    A.deviceA.Cache.ScratchState.TopRegAddress = 32;
    A.deviceA.Cache.ScratchState.addHART();
    A.deviceA.Cache.Parent = A.deviceA;
    A.deviceB.Cache.ScratchState = sf.riscv()
    A.deviceB.Cache.max_length = 10;
    A.deviceB.Cache.ScratchState.TopRegAddress = 32;
    A.deviceB.Cache.ScratchState.addHART();
    A.deviceB.Cache.Parent = A.deviceB;

    DABV0 = sf.V0()
    DABV0.Parent = A.deviceA
    DABV0.configureV0("0.0.0.0","4444",0,0);
    
    #DAB = sf.SpikeIf()
    #DAB.Parent = A.deviceA
    #DAB.setISA("RV64IMAFD");
    #DAB.SpikeArguments =("/home/commandpaul/slsv-master/test_vectors/Tests/test" + str(0) + ".rv64imafd") ;
    
    DBB = sf.SpikeIf()
    DBB.Parent = A.deviceB
    DBB.setISA("RV64IMAFD");
    DBB.SpikeArguments =("/home/commandpaul/slsv-master/test_vectors/Tests/test" + str(0) + ".rv64imafd") ;

    #A.deviceA.Bridge = DAB
    A.deviceA.Bridge = DABV0
    A.deviceB.Bridge = DBB

    SVA = sf.SVAssetrions()
    config  = [0,0,0,0]
    dv = [A.deviceA,A.deviceB]
    SVA.add_assertion(dv,1002,config)
    A.coverageTrackers.push_back(SVA)

    SVA1 = sf.SVAssetrions()
    config1  = [0,0,0,0]
    dv1 = [A.deviceA]
    SVA1.add_assertion(dv1,1,config1)
    #A.coverageTrackers.push_back(SVA1)

    A.deviceA.Bridge.Initialise()
    A.deviceB.Bridge.Initialise()    
    A.deviceA.Bridge.Synchronise()
    A.deviceB.Bridge.Synchronise()

    event = A.run();
    print("Run exited with ",format(event, '#x'))


def driver():
    #BasicSelfTests()
    LockstepVerification()
    #A.DUT.Bridge.SpikeArguments =("/home/commandpaul/slsv-master/test_vectors/Tests/test" + str(0) + ".rv64imafd") ;
    
driver()