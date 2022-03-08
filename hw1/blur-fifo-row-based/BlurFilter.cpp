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
  // initialize
  uint8_t first_row = 0;
  uint8_t last_row = 0;
  uint8_t num_of_row = 0;
  pixel row_buffer[FILTER_H][IMAGE_W + 2];
  for (uint32_t y = 0; y < FILTER_H; ++y)
    for (uint32_t x = 0; x < IMAGE_W + 2; ++x)
      row_buffer[y][x].set(0, 0 ,0);

  while (true) {
    if (num_of_row < FILTER_H - 1) {
      for (uint32_t x = 0; x < IMAGE_W + 2; ++x)
        row_buffer[last_row][x] = i_p.read();
      num_of_row++;
    } else {
      for (uint32_t x = 0; x < IMAGE_W + 2; ++x) {
        row_buffer[last_row][x] = i_p.read();
        if (x > 1)
        {
          pixel result;
          double r = 0.0, g = 0.0, b = 0.0;
          for (uint32_t v = 0; v < FILTER_H; ++v) {
            for (uint32_t u = 0; u < FILTER_W; ++u) {
              r += double(row_buffer[(first_row + v) % FILTER_H][x + u - 2].r() * filter[v][u]);
              g += double(row_buffer[(first_row + v) % FILTER_H][x + u - 2].g() * filter[v][u]);
              b += double(row_buffer[(first_row + v) % FILTER_H][x + u - 2].b() * filter[v][u]);
            }
          }
          result.set( (uint8_t)std::min(std::max(int32_t(factor * r + bias), 0), 255),
                      (uint8_t)std::min(std::max(int32_t(factor * g + bias), 0), 255),
                      (uint8_t)std::min(std::max(int32_t(factor * b + bias), 0), 255));
          o_p.write(result);
        }
      }
      first_row = (first_row + 1) % FILTER_H;
    }
    last_row = (last_row + 1) % FILTER_H;
    wait(10); //emulate module delay
  }
}