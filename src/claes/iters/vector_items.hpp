#ifndef CLAES_ITERS_VECTOR_ITEMS_HPP
#define CLAES_ITERS_VECTOR_ITEMS_HPP

#include <string>
#include "claes/iter.hpp"
#include "claes/types/vector.hpp"

namespace claes::iters {
  using namespace claes;
  using namespace std;
  
  struct VectorItems: Iter::Imp {
    using V = types::Vector::Value;

    static Iter make(const V &target) {
      return Iter(new VectorItems(target));
    }

    V target;
    V::const_iterator i, end;
    
    VectorItems(const V &target, const size_t i = 0): 
      target(target), i(this->target.begin() + i), end(this->target.end()) {}

    virtual Imp *clone() const override {
      return new VectorItems(target, i - target.begin());
    }

    virtual Iter::Result next() override {
      if (i != end) {
	return make_pair(*i, nullopt);
      }

      return make_pair(nullopt, nullopt);
    };
  };
}

#endif
