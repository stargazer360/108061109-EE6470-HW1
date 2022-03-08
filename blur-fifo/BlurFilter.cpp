#include <cmath>

#include "BlurFilter.h"

BlurFilter::BlurFilter(sc_module_name n) : sc_module(n) {
  SC_THREAD(do_filter);
  sensitive << i_clk.pos();
  dont_initialize();
  reset_signal_is(i_rst, false);
}

// blur filter
const double filter[FILTER_H][FILTER_W] = 
{
  1, 2, 1,
  2, 4, 2,
  1, 2, 1,
};

const double factor = 1.0 / 16.0;
const double bias = 0.0;

void BlurFilter::do_filter() {
  while (true) {
    double r = 0.0, g = 0.0, b = 0.0;
    pixel input, result;
    for (uint8_t y = 0; y < FILTER_H; ++y) {
      for (uint8_t x = 0; x < FILTER_W; ++x) {
        input = i_p.read();
        r += (double)input.r() * filter[y][x];
        g += (double)input.g() * filter[y][x];
        b += (double)input.b() * filter[y][x];
      }
    }
    result.set( (uint8_t)std::min(std::max(int(factor * r + bias), 0), 255),
                (uint8_t)std::min(std::max(int(factor * g + bias), 0), 255),
                (uint8_t)std::min(std::max(int(factor * b + bias), 0), 255));

    o_p.write(result);

    wait(10); //emulate module delay
  }
}