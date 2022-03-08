#include <iostream>
#include <string>
#include <cstdint>
using namespace std;

// Wall Clock Time Measurement
#include <sys/time.h>

#include "BlurFilter.h"
#include "Testbench.h"
#include "utility.h"

// TIMEVAL STRUCT IS Defined ctime
// use start_time and end_time variables to capture
// start of simulation and end of simulation
struct timeval start_time, end_time;

// int main(int argc, char *argv[])
int sc_main(int argc, char **argv) {
  if ((argc < 3) || (argc > 4)) {
    cout << "No arguments for the executable : " << argv[0] << endl;
    cout << "Usage : >" << argv[0] << " in_image_file_name out_image_file_name"
         << endl;
    return 0;
  }

  //Create modules and signals
  Testbench tb("tb");
  BlurFilter blur_filter("blur_filter");
  sc_clock clk("clk", CLOCK_PERIOD, SC_NS);
  sc_signal<bool> rst("rst");

  //Create FIFO channels
  sc_fifo<pixel> p;
  sc_fifo<pixel> result;

  //Connect FIFO channels with modules
  tb.i_clk(clk);
  tb.o_rst(rst);
  blur_filter.i_clk(clk);
  blur_filter.i_rst(rst);
  tb.o_p(p);
  tb.i_p(result);
  blur_filter.i_p(p);
  blur_filter.o_p(result);

  tb.read_bmp(argv[1]);
  sc_start();
  std::cout << "Simulated time == " << sc_core::sc_time_stamp() << std::endl;
  tb.write_bmp(argv[2]);

  return 0;
}
