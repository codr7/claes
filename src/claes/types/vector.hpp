#ifndef CLAES_TYPES_VECTOR_HPP
#define CLAES_TYPES_VECTOR_HPP

#include <vector>
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
    
    virtual E call(VM &vm, 
		   Stack &stack, 
		   int arity,
		   const Loc &loc) const override {
      vector<Cell> result;

      const auto
	i = stack.items.end() - arity,
	j = stack.items.end();

      move(i, j, back_inserter(result));
      stack.items.erase(i, j);
      stack.push(get(), result);
      return nullopt;
    }

    virtual E call(Cell &target, 
		   VM &vm, 
		   Stack &stack, 
		   int arity,
		   const Loc &loc) const override {
      switch (arity) {
      case 1: {
	const auto i = stack.pop().as(types::I64::get());
	stack.push(target.as(get())[i]);
	break;
      }
      case 2: {
	const auto v = stack.pop();
	const auto i = stack.pop().as(types::I64::get());
	target.as(get())[i] = v;
	stack.push(target);
	break;
      }
      default:
	return Error(loc, "Invalid vector call");
      }

      return nullopt;
    }

    virtual strong_ordering compare(const Cell &left, 
				    const Cell &right) const override {
      auto lvs = left.as(get()), rvs = right.as(get());

      for (const auto &li = lvs.begin(), 
	     &ri = rvs.begin();;) {
	if (li == lvs.end()) {
	  return strong_ordering::less;
	}

	if (ri == rvs.end()) {
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

    virtual void push(Cell &target, const Cell &item) const override {
      target.as(get()).push_back(item);
    }
  };
}

#endif
