#ifndef CLAES_ITERS_I64_RANGE_HPP
#define CLAES_ITERS_I64_RANGE_HPP

#include <iostream>

#include "claes/iter.hpp"
#include "claes/types/i64.hpp"

namespace claes::iters {
  using namespace claes;
  
  struct I64Range: Iter::Imp {
    static Iter make(const types::I64::Value i, const types::I64::Value j) {
      return Iter(new I64Range(i, j));
    }

    types::I64::Value i, j;

    I64Range(const types::I64::Value i, const types::I64::Value j): i(i), j(j) {}

    virtual Imp *clone() const override {
      return new I64Range(i, j);
    }

    virtual Iter::Result next() override {
      if (i < j) {
	return make_pair(Cell(types::I64::get(), i++), nullopt);
      }

      return make_pair(nullopt, nullopt);
    };
  };
}

#endif
