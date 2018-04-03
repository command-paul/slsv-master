
from SLSV_test import TestClass as _TestClass
from SLSV import slsv_target


class testInterface(_TestClass):
    V0inst = slsv_target.V0()
    def setup(self):
        self.V0inst.configureV0("0.0.0.0","4444",6,64)
        #self.V0inst.Initialise()
        return True
    def test(self):
        #self.V0inst.Single_Step()
        return True
    def getResult(self):
        return True