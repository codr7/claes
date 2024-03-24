#include "claes/iters/vector_items.hpp"
#include "claes/stack.hpp"
#include "claes/types/i64.hpp"
#include "claes/types/iter.hpp"
#include "claes/types/vector.hpp"

namespace claes::types {
  E Vector::call(VM &vm, 
		 Stack &stack, 
		 int arity,
		 const claes::Loc &loc) const {
    vector<Cell> result;

    const auto
      i = stack.end() - arity,
      j = stack.end();

    move(i, j, back_inserter(result));
    stack.items.erase(i, j);
    stack.push(get(), result);
    return nullopt;
  }

  E Vector::call(Cell &target, 
		 VM &vm, 
		 Stack &stack, 
		 int arity,
		 bool recursive,
		 const claes::Loc &loc) const {
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

  strong_ordering Vector::compare(const Cell &left, 
				  const Cell &right) const {
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

  void Vector::dump(const Cell &value, ostream &out) const {
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

  bool Vector::eq(const Cell &left, const Cell &right) const {
    return left.as(get()) == right.as(get());
  }
    
  Cell Vector::iter(const Cell &target) const {
    return Cell(Iter::get(), iters::VectorItems::make(target.as(get())));
  }

  bool Vector::is_true(const Cell &value) const {
    return !value.as(get()).empty();
  }

  void Vector::push(Cell &target, const Cell &item) const {
    target.as(get()).push_back(item);
  }
}
