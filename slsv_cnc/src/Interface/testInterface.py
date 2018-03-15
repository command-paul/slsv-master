import slsv_interface
IF = slsv_interface.V0()
IF.configureV0('0.0.0.0','4444',0,0)
IF.Initialise()
updates = IF.Single_Step()