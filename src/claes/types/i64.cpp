#include "claes/iters/i64_range.hpp"
#include "claes/types/i64.hpp"
#include "claes/types/iter.hpp"

namespace claes::types {
  Cell I64::iter(const Cell &target) const {
    return Cell(Iter::get(), iters::I64Range::make(0, target.as(get())));
  }

}
