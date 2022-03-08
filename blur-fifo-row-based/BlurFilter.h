#ifndef BLUR_FILTER_H_
#define BLUR_FILTER_H_

#include <cstdint>
#include <systemc>
using namespace sc_core;

#include "utility.h"

class BlurFilter : public sc_module {
public:
  sc_in_clk i_clk;
  sc_in<bool> i_rst;
  sc_fifo_in<pixel> i_p;
  sc_fifo_out<pixel> o_p;

  SC_HAS_PROCESS(BlurFilter);
  BlurFilter(sc_module_name n);
  ~BlurFilter() = default;

private:
  void  do_filter();
};
  
#endif
