#ifndef CLAES_ITERS_ONCE_HPP
#define CLAES_ITERS_ONCE_HPP

#include "claes/iter.hpp"

namespace claes::iters {
  using namespace claes;
  
  struct Once: Iter::Imp {
    static Iter make(const claes::Cell &target) {
      return Iter(new Once(target));
    }

    optional<claes::Cell> value;

    Once(const claes::Cell &value): value(value) {}

    virtual Iter::Result next() {
      if (value) {
	const auto result = *value;
	value.reset();
	return make_pair(result, nullopt);
      }

      return make_pair(nullopt, nullopt);
    };

    virtual void dump(ostream &out) const {
      if (value) {
	out << *value;
      } else {
	out << '_';
      }
    }
  };
}

#endif
