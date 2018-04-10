#include "SpikeIf.hpp"

#include <iostream>
#include <vector>
#include <string>

//
void sim_thread_main(void* arg)
{
  ((sim_t*)arg)->main();
}

void sim_t::main()  // This is private called somewhere in the start routine and when things need to comm with htif periphrals which we dont care about
{
  step(1);
  //if (remote_bitbang) remote_bitbang->tick();
}

void sim_t::set_log(bool value){
  step(1);
}

// int htif_t::run()
// {
//   start();
//   //load_program();
//   target.switch_to()
//   //idle();
//   stop();
//   //device_list.tick();  
//   return exit_code();
// }
// Patches Overrideing Spike & Htif functions

void sim_t::step(size_t n)
{
  if (remote_bitbang) remote_bitbang->tick(); // This was added here  it is functionally eqv
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
    }
  }
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
  SpikeArguments = "-H --rbb-port=10001 /home/commandpaul/slsv-master/test_vectors/Tests/loop0.rv64imafd ";
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
  bool use_rbb = true;
  unsigned progsize = 2;
  unsigned max_bus_master_bits = 0;
  std::vector<int> hartids;


  //auto argv1 = parser.parse(A);
  //std::cout << argv1 << std::endl;
  //std::vector<std::string> htif_args();
  if (mems.empty())
    mems = make_mems("2048");

  std::vector<std::string> htif_args;
  htif_args.push_back("/home/commandpaul/slsv-master/test_vectors/Tests/test0.rv64imafd");

  //htif_args.push_back(SpikeArguments);

  sim_t s(isa, nprocs, halted, start_pc, mems, htif_args, std::move(hartids),
      progsize, max_bus_master_bits);
  std::unique_ptr<remote_bitbang_t> remote_bitbang((remote_bitbang_t *) NULL);
  std::unique_ptr<jtag_dtm_t> jtag_dtm(new jtag_dtm_t(&s.debug_module));
  if (use_rbb) {
    remote_bitbang.reset(new remote_bitbang_t(rbb_port, &(*jtag_dtm)));
    s.set_remote_bitbang(&(*remote_bitbang));
  }
  
  for (size_t i = 0; i < nprocs; i++)
  {
    if (ic) s.get_core(i)->get_mmu()->register_memtracer(&*ic);
    if (dc) s.get_core(i)->get_mmu()->register_memtracer(&*dc);
    if (extension) s.get_core(i)->register_extension(extension());
  }

  s.set_debug(debug);
  s.set_histogram(histogram);
  
  s.run(); // Essentially initialises everything :P
  std::cout<< "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl ;
  //while(!done()){
  //s.main();
  s.set_log(log);
  processor_t HART0 = *(s.get_core(0)); // make this compatible with slsv interface addressing and access.
  
  //Members of processor_t
  //reg_t get_csr(int which);
  //mmu_t* get_mmu() { return mmu; }
  //state_t* get_state() { return &state; }
  std::cout << HART0.get_csr(2816) << std::endl;
  //mmu_t hart0mmu = *(HART0.get_mmu());
  state_t hart0state = *(HART0.get_state());
  // use spike bus_t to access memory mapped IO . but bus is private and i will have to seriously modify something to get it :(
  //Members of state_t
  //reg_t pc;
  //regfile_t<reg_t, NXPR, true> XPR;
  //regfile_t<freg_t, NFPR, false> FPR;
  std::cout << hart0state.pc << std::endl;
  std::cout << hart0state.XPR[0] << std::endl;
  while(hart0state.pc <= 0x80000020){
    s.set_log(log);
    HART0 = *(s.get_core(0)); // make this compatible with slsv interface addressing and access.
    std::cout << std::hex << HART0.get_csr(2816) << std::endl;
    hart0state = *(HART0.get_state());
    std::cout << std::hex << hart0state.pc << std::endl;
    std::cout << std::hex << hart0state.XPR[0] << std::endl;
  }
  std::cout<< "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl ;
  //idle();//target.switch_to();
  s.stop();
  return true;
}

bool SpikeIf::Synchronise() {
  return true;
}

std::pair<std::vector<std::pair<uint32_t,uint64_t>>,std::vector<std::pair<uint64_t,uint64_t>>> SpikeIf::Single_Step() {
  std::pair<std::vector<std::pair<uint32_t,uint64_t>>,std::vector<std::pair<uint64_t,uint64_t>>> A;
  return A;
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


// Reference implementations 
// int main(int argc, char** argv)
// {
//   bool debug = false;
//   bool halted = false;
//   bool histogram = false;
//   bool log = false;
//   bool dump_dts = false;
//   size_t nprocs = 1;
//   reg_t start_pc = reg_t(-1);
//   std::vector<std::pair<reg_t, mem_t*>> mems;
//   std::unique_ptr<icache_sim_t> ic;
//   std::unique_ptr<dcache_sim_t> dc;
//   std::unique_ptr<cache_sim_t> l2;
//   std::function<extension_t*()> extension;
//   const char* isa = DEFAULT_ISA;
//   uint16_t rbb_port = 0;
//   bool use_rbb = false;
//   unsigned progsize = 2;
//   unsigned max_bus_master_bits = 0;
//   std::vector<int> hartids;

//   auto const hartids_parser = [&](const char *s) {
//     std::string const str(s);
//     std::stringstream stream(str);

//     int n;
//     while (stream >> n)
//     {
//       hartids.push_back(n);
//       if (stream.peek() == ',') stream.ignore();
//     }
//   };

//   option_parser_t parser;
//   parser.help(&help);
//   parser.option('h', 0, 0, [&](const char* s){help();});
//   parser.option('d', 0, 0, [&](const char* s){debug = true;});
//   parser.option('g', 0, 0, [&](const char* s){histogram = true;});
//   parser.option('l', 0, 0, [&](const char* s){log = true;});
//   parser.option('p', 0, 1, [&](const char* s){nprocs = atoi(s);});
//   parser.option('m', 0, 1, [&](const char* s){mems = make_mems(s);});
//   // I wanted to use --halted, but for some reason that doesn't work.
//   parser.option('H', 0, 0, [&](const char* s){halted = true;});
//   parser.option(0, "rbb-port", 1, [&](const char* s){use_rbb = true; rbb_port = atoi(s);});
//   parser.option(0, "pc", 1, [&](const char* s){start_pc = strtoull(s, 0, 0);});
//   parser.option(0, "hartids", 1, hartids_parser);
//   parser.option(0, "ic", 1, [&](const char* s){ic.reset(new icache_sim_t(s));});
//   parser.option(0, "dc", 1, [&](const char* s){dc.reset(new dcache_sim_t(s));});
//   parser.option(0, "l2", 1, [&](const char* s){l2.reset(cache_sim_t::construct(s, "L2$"));});
//   parser.option(0, "isa", 1, [&](const char* s){isa = s;});
//   parser.option(0, "extension", 1, [&](const char* s){extension = find_extension(s);});
//   parser.option(0, "dump-dts", 0, [&](const char *s){dump_dts = true;});
//   parser.option(0, "extlib", 1, [&](const char *s){
//     void *lib = dlopen(s, RTLD_NOW | RTLD_GLOBAL);
//     if (lib == NULL) {
//       fprintf(stderr, "Unable to load extlib '%s': %s\n", s, dlerror());
//       exit(-1);
//     }
//   });
//   parser.option(0, "progsize", 1, [&](const char* s){progsize = atoi(s);});
//   parser.option(0, "debug-sba", 1,
//       [&](const char* s){max_bus_master_bits = atoi(s);});

//   auto argv1 = parser.parse(argv);
//   std::vector<std::string> htif_args(argv1, (const char*const*)argv + argc);
//   if (mems.empty())
//     mems = make_mems("2048");

//   sim_t s(isa, nprocs, halted, start_pc, mems, htif_args, std::move(hartids),
//       progsize, max_bus_master_bits);
//   std::unique_ptr<remote_bitbang_t> remote_bitbang((remote_bitbang_t *) NULL);
//   std::unique_ptr<jtag_dtm_t> jtag_dtm(new jtag_dtm_t(&s.debug_module));
//   if (use_rbb) {
//     remote_bitbang.reset(new remote_bitbang_t(rbb_port, &(*jtag_dtm)));
//     s.set_remote_bitbang(&(*remote_bitbang));
//   }

//   if (dump_dts) {
//     printf("%s", s.get_dts());
//     return 0;
//   }

//   if (!*argv1)
//     help();

//   if (ic && l2) ic->set_miss_handler(&*l2);
//   if (dc && l2) dc->set_miss_handler(&*l2);
//   for (size_t i = 0; i < nprocs; i++)
//   {
//     if (ic) s.get_core(i)->get_mmu()->register_memtracer(&*ic);
//     if (dc) s.get_core(i)->get_mmu()->register_memtracer(&*dc);
//     if (extension) s.get_core(i)->register_extension(extension());
//   }

//   s.set_debug(debug);
//   s.set_log(log);
//   s.set_histogram(histogram);
//   return s.run();
// }
