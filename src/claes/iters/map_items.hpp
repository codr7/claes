#ifndef CLAES_ITERS_MAP_ITEMS_HPP
#define CLAES_ITERS_MAP_ITEMS_HPP

#include <string>
#include "claes/iter.hpp"
#include "claes/types/map.hpp"
#include "claes/types/pair.hpp"

namespace claes::iters {
  using namespace claes;
  using namespace std;
  
  struct MapItems: Iter::Imp {
    using M = types::Map::Value;

    static Iter make(const M &target) {
      return Iter(new MapItems(target));
    }

    M target;
    M::const_iterator end;
    M::const_iterator i;
    size_t n;
    
    MapItems(const M &target, const size_t n = 0): 
      target(target), end(this->target.end()), i(this->target.begin()), 
      n(n) {
      for (int _ = 0; _ < n; _++, i++);
    }

    virtual Imp *clone() const override {
      return new MapItems(target, n);
    }

    virtual Iter::Result next() override {
      if (i != end) {
	n++;
	return make_pair(Cell(types::Pair::get(), *i++), nullopt);
      }

      return make_pair(nullopt, nullopt);
    };
  };
}

#endif
