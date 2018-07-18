##### This is a work in progress with modifications being made over time.
# SLSV
## The Shakti Lock-Step Verification Framework
### A Scriptable Scalabale Interface Agnostic Framework To Functionally Verify RISC-V SOCs
##### DOXYGEN DOCS of the CPP Backend :: https://codedocs.xyz/command-paul/slsv-master/

### Requirements
riscv-gcc,riscv-gdb (unknown-elf-64)    
Cmake 3.x      
Swig 3.x - and make sure all remaining fragments of swig 2 are obliterated.       
GCC 5.x +       
Python3       
(For Lock Step Verification with Risc-V ISA SIM -aka spike)        
RISCV ISA SIM - Latest Commit on RISC-V Tools       
(With  Emulation / Post Silicon Targets With a RISC-V Debug Spec 0.13 Debug module - Pseudo Data Trace)     
SLSV-RISC-V-OPENOCD - Submodule      


### Build Instructions
#### Clone This Repository::
```bash
git clone https://github.com/command-paul/slsv-master.git
# Clone Submodules : slsv-riscv-opepnocd .. recursive ..
git submodule update --init --recursive
```

#### in /slsv_cnc:
```bash
cmake .
make
sudo make install
```
#### Build slsv-riscv-openocd in /slsv-riscv-openocd
```bash
./bootstrap
./configure --enable-remote-bitbang --enable-jtag_vpi --enable-jlink
make
# The install command will replace your riscv-tools openocd at $RISCV.
# This fork routinely pulls changes from upstream.
sudo make install
```

### Running An Example

After Completing the above and having your environment setup.
Run , from this repository root.
```bash
python3 SpikeVSpike.py
```
This Runs Test Pre compiled test vectors in /test_vectors/rv64g-p-tests
And Terminates IFF PC == 0x80000048 , in the Test Pass Section of the RISC-V Tests

##### Credits and Gratitude to 
###### The RISC-V Foundation and the developers and maintainers of the RISC-V Software Ecosystem
###### Team Shakti - CASL - RISE Lab IIT Madras     
###### Open Source With <3 , IITM Licence.
