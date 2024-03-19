#include "claes/iters/runes.hpp"
#include "claes/types/iter.hpp"
#include "claes/types/string.hpp"

namespace claes::types {
  Cell String::iter(const Cell &target) const {
    return Cell(types::Iter::get(), iters::Runes::make(target.as(get())));
  }

}
