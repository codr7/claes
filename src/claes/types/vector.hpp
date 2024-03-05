#ifndef CLAES_TYPES_VECTOR_HPP
#define CLAES_TYPES_VECTOR_HPP

#include <vector>
#include "claes/cell.hpp"
#include "claes/type.hpp"

namespace claes::types {
  using namespace claes;

  struct Vector: Type::Imp {
    using Value = vector<Cell>;
    
    static TType<Vector> get() {
      static TType<Vector> t("Vector");
      return t;
    }    

    Vector(const string &name): Type::Imp(name) {}

    virtual void dump(const Cell &value, ostream &out) const override {
      out << '[';
      
      auto i = 0;
      for (const auto &it: value.as(get())) {
	if (i++ > 0) {
	  out << ' ';
	}

	out << it;
      }

      out << ']';
    }
    
    virtual bool eq(const Cell &left, const Cell &right) const override {
      return left.as(get()) == right.as(get());
    }

    virtual bool is_true(const Cell &value) const override {
      return !value.as(get()).empty();
    }
  };
}

#endif
