#ifndef CLAES_ITERS_RUNES_HPP
#define CLAES_ITERS_RUNES_HPP

#include <string>
#include "claes/iter.hpp"
#include "claes/types/rune.hpp"

namespace claes::iters {
  using namespace claes;
  using namespace std;
  
  struct Runes: Iter::Imp {
    static Iter make(const string &target) {
      return Iter(new Runes(target));
    }

    string target;
    string::const_iterator i, end;
    
    Runes(const string &target, const size_t i = 0): 
      target(target), i(this->target.begin() + i), end(this->target.end()) {}

    virtual Imp *clone() const override {
      return new Runes(target, i - target.begin());
    }

    virtual Iter::Result next() override {
      if (i != end) {
	return make_pair(Cell(types::Rune::get(), *i++), nullopt);
      }

      return make_pair(nullopt, nullopt);
    };
  };
}

#endif
