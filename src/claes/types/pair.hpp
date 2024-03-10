#ifndef CLAES_TYPES_PAIR_HPP
#define CLAES_TYPES_PAIR_HPP

#include "claes/cell.hpp"
#include "claes/type.hpp"

namespace claes::types {
  using namespace claes;

  struct Pair: Type::Imp {
    using Value = pair<Cell, Cell>;
    
    static TType<Pair> get() {
      static TType<Pair> t("Pair");
      return t;
    }    

    Pair(const string &name): Type::Imp(name) {}

    virtual strong_ordering compare(const Cell &left, 
				    const Cell &right) const override {
      return left.as(get()) <=> right.as(get());
    }

    virtual void dump(const Cell &value, ostream &out) const override {
      const auto &p = value.as(get());
      out << p.first << ':' << p.second;
    }
    
    virtual bool eq(const Cell &left, const Cell &right) const override {      
      const auto &lp = left.as(get()), &rp = right.as(get());
      return lp.first == rp.first && lp.second == rp.second;
    }
  };
}

#endif
