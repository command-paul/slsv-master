# Python tests for the SWIG wrapped State container class

from SLSV_test import TestClass as _TestClass
from SLSV import slsv_target

class testState(_TestClass):
    riscv = slsv_target.riscv()
    def setup(self):
        self.riscv.addHART()
        self.riscv.addHART()
        self.riscv.addMemory()
        self.riscv.addNHSV()
        return True
    def test(self):
        print(self.riscv.HART_Vec.size())
        self.riscv.HART_Vec[0].GPR[0] = 0x9000
        print(self.riscv.HART_Vec[0].GPR[0])
        return True
    def getResult(self):
        self.riscv
        return True
