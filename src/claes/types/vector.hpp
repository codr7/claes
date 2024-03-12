#ifndef CLAES_TYPES_VECTOR_HPP
#define CLAES_TYPES_VECTOR_HPP

#include "claes/type.hpp"
#include "claes/vector.hpp"

namespace claes::types {
  using namespace claes;

  struct Vector: Type::Imp {
    using Value = claes::Vector;
    
    static TType<Vector> get() {
      static TType<Vector> t("Vector");
      return t;
    }    

    Vector(const string &name): Type::Imp(name) {}

    virtual strong_ordering compare(const Cell &left, 
				    const Cell &right) const override {
      auto lvs = left.as(get()), rvs = right.as(get());

      for (const auto &li = lvs.imp->items.begin(), 
	     &ri = rvs.imp->items.begin();;) {
	if (li == lvs.imp->items.end()) {
	  return strong_ordering::less;
	}

	if (ri == rvs.imp->items.end()) {
	  return strong_ordering::greater;
	}

	auto lv = *li, rv = *ri;

	if (const auto r = lv <=> rv; r != strong_ordering::equal) {
	  return r;
	}
      }

      return strong_ordering::equal;
    }

    virtual void dump(const Cell &value, ostream &out) const override {
      out << '[';
      
      auto i = 0;
      for (const auto &it: value.as(get()).imp->items) {
	if (i++ > 0) {
	  out << ' ';
	}

	out << it;
      }

      out << ']';
    }
    
    virtual bool eq(const Cell &left, const Cell &right) const override {
      return left.as(get()).imp->items == right.as(get()).imp->items;
    }

    virtual bool is_true(const Cell &value) const override {
      return !value.as(get()).imp->items.empty();
    }

    virtual Cell push(const Cell &target, const Cell &item) const override {
      target.as(get()).imp->items.push_back(item);
      return target;
    }
  };
}

#endif
