#ifndef CLAES_ITERS_REPEAT_HPP
#define CLAES_ITERS_REPEAT_HPP

#include "claes/iter.hpp"

namespace claes::iters {
  using namespace claes;
  
  struct Repeat: Iter::Imp {
    static Iter make(const claes::Cell &value, const int n) {
      return Iter(new Repeat(value, n));
    }

    int n;
    claes::Cell value;

    Repeat(const claes::Cell &value, const int n): n(n), value(value) {}

    virtual Imp *clone() const override {
      return new Repeat(value, n);
    }

    virtual Iter::Result next() override {
      if (n) {
	n--;
	return make_pair(value, nullopt);
      }

      return make_pair(nullopt, nullopt);
    };
  };
}

#endif
