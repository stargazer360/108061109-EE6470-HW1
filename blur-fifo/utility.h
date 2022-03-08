#ifndef UTILITY_H_
#define UTILITY_H_

#define FILTER_H 3
#define FILTER_W 3

#include <cstdint>
#include <iostream>
#include <string>
using namespace std;

#include <systemc>
using namespace sc_core;

// store RGB channels of a pixel, available for sc_fifo<>
class pixel
{
private:
  uint8_t _r;
  uint8_t _g;
  uint8_t _b;
public:
  pixel(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0)
    : _r(r), _g(g), _b(b){};

  pixel& operator=(const pixel& in) 
  {
    _r = in._r;
    _g = in._g;
    _b = in._b;
    return *this;
  }

  uint8_t r() const {return _r;}
  uint8_t g() const {return _g;}
  uint8_t b() const {return _b;}

  void set(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0)
  {
    _r = r;
    _g = g;
    _b = b;
  }

  friend ostream& operator<<(ostream& file, const pixel&);
  friend void sc_trace(sc_trace_file*& tf, const pixel&, std::string nm);
};

#endif