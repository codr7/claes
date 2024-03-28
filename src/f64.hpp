#pragma once

#include <cstdint>

namespace f64 {
  using T = uint64_t;
  const auto EXP_BITS = 4;

  inline uint64_t scale(uint8_t exp) {
    uint64_t s = 1;
    while (exp--) { s *= 10; }
    return s;
  }

  inline T make(const uint8_t exp, const uint64_t val) {
    return (T)((exp & ((1 << EXP_BITS) - 1)) + (val << EXP_BITS));
  }

  inline uint8_t exp(const T x) { 
    return x & ((1 << EXP_BITS) - 1); 
  }

  inline uint64_t val(const T x) { 
    return x >> EXP_BITS; 
  }


  inline T frac(T x) {
    auto xv = val(x), xs = scale(exp(x));
    return xv - (xv / xs) * xs;
  }

  inline T add(const T x, const T y) {
    const auto xe = exp(x);
    return make(xe, val(x) + val(y) * scale(xe) / scale(exp(y)));
  }

  inline T div(const T x, const T y) {
    return make(exp(x), val(x) / (val(y) / scale(exp(y))));
  }

  inline T mul(const T x, const T y) {
    return make(exp(x), val(x) * val(y) / scale(exp(y)));
  }

  inline T sub(const T x, const T y) {
    const auto xe = exp(x);
    return make(xe, val(x) - val(y) * scale(xe) / scale(exp(y)));
  }

  inline T trunc(T x) { 
    return val(x) / scale(exp(x)); 
  }
}
