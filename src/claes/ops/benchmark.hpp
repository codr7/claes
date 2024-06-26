#ifndef CLAES_OPS_BENCHMARK_HPP
#define CLAES_OPS_BENCHMARK_HPP

#include "claes/op.hpp"
#include "claes/types/i64.hpp"

namespace claes::ops {
  using namespace claes;
  
  struct Benchmark: Op::Imp {
    types::I64::Value repetitions;

    Benchmark(types::I64::Value repetitions):
      Op::Imp(Op::Code::BENCHMARK), repetitions(repetitions) {}

    virtual void trace(VM &vm, ostream &out) const override {
      out << "Benchmark repetitions: " << repetitions;
    }
  };
}

#endif
