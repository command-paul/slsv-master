// This is a module that interacts with the mitplv formal model 
// This is a future piece that should tie into the haskell model directly l

// The RS-Nikhil FFI :: Machine_State container :|

// -- Architectural state
//                   f_pc   :: Word64,
//                   f_gprs :: GPR_File,
//                   f_csrs :: CSR_File,
//                   f_priv :: Priv_Level,
//                   -- Memory and mory mapped IO
//                   f_mem  :: Mem,
//                   f_mmio :: MMIO,
//                   -- Implementation options
//                   f_mem_addr_ranges :: [(Word64, Word64)],    -- list of (addr_start, addr_lim)
//                   -- For convenience and debugging only; no semantic relevance
//                   f_rv        :: RV,   -- redundant copy of info in CSR MISA
//                   f_verbosity :: Int,
//                   f_run_state :: Run_State
// 
                  
// Wriiting an FFI to the non marshallable MAchine State module isgoing to be a monumental task , it would be better to prove the other model .
// developa a better model for interfacing all sorts of formal models - a multi threaded - multi system scalable model
// Right now I am going to write the processor for the tandem verification scheme. with simple equaltiy assertion between the models.

