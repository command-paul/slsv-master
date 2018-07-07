#include "SpikeIf.hpp"

#include <iostream>
#include <vector>
#include <string>

//
void sim_t::main()  // This is private called somewhere in the start routine and when things need to comm with htif periphrals which we dont care about
{
  step(1);
  //if (remote_bitbang) remote_bitbang->tick();
}

void sim_t::set_log(bool value){
  step(1);
}

void sim_t::step(size_t n)
{
  //if (remote_bitbang) remote_bitbang->tick(); // This was added here  it is functionally eqv
  for (size_t i = 0, steps = 0; i < n; i += steps)
  {
    steps = std::min(n - i, INTERLEAVE - current_step);
    procs[current_proc]->step(steps);

    current_step += steps;
    if (current_step == INTERLEAVE)
    {
      current_step = 0;
      procs[current_proc]->yield_load_reservation();
      if (++current_proc == procs.size()) {
        current_proc = 0;
        clint->increment(INTERLEAVE / INSNS_PER_RTC_TICK);
      }
      //host->switch_to(); // This affects the ability of spike to terminate on infinite loops.
      // There are 2 contexts one host target , There is current an error with some sort of improper initialisation
      // which prints an error message when host->switch_to() is called . // figure out that for htif periphral compatibility.
    }
  }
}

void sim_thread_main(void* arg) //  ref:: sim_t ::main()
{
  ((sim_t*)arg)->main();
}

int sim_t::run()  // This method just initialises and loads the binary.
{
  host = context_t::current();
  target.init(sim_thread_main, this);
  htif_t::start();
  return 0;
}

// The SpikeIf Transport Interface module Members defined 
SpikeIf::SpikeIf(){
  std::cout << "Special SLSV Interface Instance Spawned" << std::endl ;
  return;
}
SpikeIf::~SpikeIf() {
  std::cout << "Special SLSV Interface Instance Destroyed" << std::endl ;
  return;
}

bool SpikeIf::destroy_s(){
  if(s != NULL){
    s->stop();
    delete s;
    std::cout << "Special SLSv Sim_t deleted" << std::endl ;
    return true;
  }
  return false;
}

bool SpikeIf::setISA(std::string){
  return true;
}

bool SpikeIf::setProcessors(u_int16_t){
  return true;
}

bool SpikeIf::setMiB(u_int16_t){
  return true;
}

bool SpikeIf::setMVect(std::vector<std::pair<uint64_t,u_int64_t>>){
  return true;
}

bool SpikeIf::setPC(uint64_t){
  return true;
}

bool SpikeIf::setPK(){
  return true;
}

bool SpikeIf::setElfToLoad(){
  return true;
}

bool SpikeIf::setHalted(bool Halted){
  return true;
}

bool SpikeIf::genSpikeArguments(){
  return true;
}

static std::vector<std::pair<reg_t, mem_t*>> make_mems(const char* arg)
{
  // handle legacy mem argument
  char* p;
  auto mb = strtoull(arg, &p, 0);
  if (*p == 0) {
    reg_t size = reg_t(mb) << 20;
    if (size != (size_t)size)
      throw std::runtime_error("Size would overflow size_t");
    return std::vector<std::pair<reg_t, mem_t*>>(1, std::make_pair(reg_t(DRAM_BASE), new mem_t(size)));
  }

  // handle base/size tuples
  std::vector<std::pair<reg_t, mem_t*>> res;
  while (true) {
    auto base = strtoull(arg, &p, 0);
    auto size = strtoull(p + 1, &p, 0);
    res.push_back(std::make_pair(reg_t(base), new mem_t(size)));
    if (!*p)
      break;
    arg = p + 1;
  }
  return res;
}

bool SpikeIf::Initialise() {
  bool debug = false;
  bool halted = false;
  bool histogram = false;
  bool log = false;
  //bool dump_dts = false;
  size_t nprocs = 1;
  reg_t start_pc = reg_t(-1);
  std::vector<std::pair<reg_t, mem_t*>> mems;
  std::unique_ptr<icache_sim_t> ic;
  std::unique_ptr<dcache_sim_t> dc;
  std::unique_ptr<cache_sim_t> l2;
  std::function<extension_t*()> extension;
  const char* isa = DEFAULT_ISA;
  uint16_t rbb_port = 0;
  bool use_rbb = false;
  unsigned progsize = 2;
  unsigned max_bus_master_bits = 0;
  std::vector<int> hartids;


  //auto argv1 = parser.parse(A);
  //std::cout << argv1 << std::endl;
  //std::vector<std::string> htif_args();
  if (mems.empty())
    mems = make_mems("2048");

  std::vector<std::string> htif_args;
  htif_args.push_back(SpikeArguments);

  //htif_args.push_back(SpikeArguments);

  s = new sim_t(isa, nprocs, halted, start_pc, mems, htif_args, std::move(hartids),progsize, max_bus_master_bits,0);
          //sim_t(isa,_nprocs, halted,start_pc , mems, args     , const std::vector<int> hartids,unsigned progsize, unsigned max_bus_master_bits, bool require_authentication); // Updated interface for new commit
      
  std::unique_ptr<remote_bitbang_t> remote_bitbang((remote_bitbang_t *) NULL);
  std::unique_ptr<jtag_dtm_t> jtag_dtm(new jtag_dtm_t(&s->debug_module));
  if (use_rbb) {
    remote_bitbang.reset(new remote_bitbang_t(rbb_port, &(*jtag_dtm)));
   s->set_remote_bitbang(&(*remote_bitbang));
  }
  
  for (size_t i = 0; i < nprocs; i++)
  {
    if (ic)s->get_core(i)->get_mmu()->register_memtracer(&*ic);
    if (dc)s->get_core(i)->get_mmu()->register_memtracer(&*dc);
    if (extension)s->get_core(i)->register_extension(extension());
  }

 s->set_debug(debug);
 s->set_histogram(histogram);
  
 s->run(); // Essentially initialises everything :P
  //std::cout<< "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl ;
  //while(!done()){
  //s.main();
 s->set_log(log);
  processor_t* HART0 =s->get_core(0); // make this compatible with slsv interface addressing and access.
  
  //Members of processor_t
  //reg_t get_csr(int which);
  //mmu_t* get_mmu() { return mmu; }
  //state_t* get_state() { return &state; }
  //std::cout << std::hex << HART0->get_csr(2816) << std::endl;
  //mmu_t hart0mmu = *(HART0.get_mmu());
  state_t* hart0state = HART0->get_state();
  // use spike bus_t to access memory mapped IO . but bus is private and i will have to seriously modify something to get it :(
  //Members of state_t
  //reg_t pc;
  //regfile_t<reg_t, NXPR, true> XPR;
  //regfile_t<freg_t, NFPR, false> FPR;
  //std::cout << std::hex << hart0state->pc << std::endl;
  //std::cout << std::hex << hart0state->XPR[0] << std::endl;
  return true;
}

bool SpikeIf::Synchronise() {
  processor_t* HART0 =s->get_core(0);
  state_t* hart0state = HART0->get_state();
  //std::cout << std::hex << hart0state->pc << std::endl;
  while(hart0state->pc <= 0x80000000){
    s->set_log(0);
    //std::cout << "lop" << std::endl;
    //HART0 =s->get_core(0); // make this compatible with slsv interface addressing and access.
    //std::cout << std::hex << HART0->get_csr(2816) << std::endl;
    //hart0state = HART0->get_state();
    //std::cout << std::hex << hart0state->pc << std::endl;
    //std::cout << std::hex << hart0state->XPR[0] << std::endl;
  }
  //std::cout<< "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl ;
  //s.target.switch_to();
  return true;
}

uint32_t SpikeIf::Single_Step() {
  traceFrame_t updates;
	uint32_t event = ALL_OK; // ref events.hpp	
	std::cout << "<<<<<<" << std::endl;
	uint32_t iterator = 0;
// 	MEMORY
	UpdateFrame_t MemUpdates;
// 	CSR GPR FPR
	UpdateFrame_t RegUpdates;
	processor_t* HART0 =s->get_core(0);
  state_t* hart0state = HART0->get_state();
  
  // This is the hak that actually single
  s->set_log(0);
  
  
  HART0 =s->get_core(0); // make this compatible with slsv interface addressing and access.
  //std::cout << std::hex << HART0->get_csr(2816) << std::endl;
  hart0state = HART0->get_state();
  riscv* hartPtr = Parent->Cache->ScratchState;
	
  // just getting GPR`s , PC and FPR for now
	uint32_t MaxRegs = hartPtr->TopRegAddress;
	uint32_t HartCT  = hartPtr->HART_Vec.size(); // apparently some 2^20 harts now :P 
	// The fetch method does nont currently et the hartsel value 
	for(int HartIter = 0 ; HartIter < HartCT ; HartIter++){
		uint64_t value;
		for(uint i = 0 ; i <= MaxRegs; i ++){
      
      if(i<32) value = hart0state->XPR[i];
      else if(i==32) value = hart0state->pc;
      //else if(i<65) value =(uint64_t) 
      uint64_t csval = hartPtr->get_register(i);
			if(value != csval){
				// Check if this is an update , if not skip // Resolve after reference to state container is sorted
				std::cout << i << "\t" << std::hex << value << "OLD :: ONDEV " << std::hex << csval <<std::endl;
				// The I being comitted here needs to be transelated to the required address
				update_t temp = std::make_pair(i,value);
				RegUpdates.push_back(temp);
			}	
	  	}
		// CSR
	}

// 	NHSV
	updates = std::make_pair(RegUpdates,MemUpdates);
	event = Parent->Cache->enqueueTF(updates);
/*	
	If Sate-> cached == Variable read //nothing
	else // Create update and append to the appropriate vector for setting into the trace cache 


	//updates.first = Reg_update_vector; // I suspect this is horribly leaky
	//updates.second = Mem_update_vector;
	// = (traceFrame) std::make_pair(Reg_update_vector,Mem_update_vector);
	*/
	// Partent->traceCache.cache(updates);
	// free updates ?? update and free all liabilities of the interface file ??? -  yasss good in long run as everyone fends for his / her own memory
	//std::cout << "<<<<<<" << std::endl;
	return event;
}

std::pair<uint64_t,std::vector<uint32_t>> SpikeIf::GetVariable() {
  std::pair<uint64_t,std::vector<uint32_t>> A;
  return A;
}

bool SpikeIf::SetVariable() {
  return true;
}

std::pair<uint64_t,std::vector<uint32_t>> SpikeIf::GetMemory() {
  std::pair<uint64_t,std::vector<uint32_t>> A;
  return A;
}

bool SpikeIf::SetMemory() {
  return true;
}

std::pair<uint64_t,std::vector<uint32_t>> SpikeIf::DumpMemory() {
  std::pair<uint64_t,std::vector<uint32_t>> A;
  return A;
}

bool SpikeIf::LoadBinary(uint64_t address) {
  return true;
}

bool SpikeIf::Checkpoint(std::string File) {
  return true;
}

bool SpikeIf::Checkpoint(){
  return true;
} 

bool SpikeIf::Restore(std::string File) {
  return true;
}
